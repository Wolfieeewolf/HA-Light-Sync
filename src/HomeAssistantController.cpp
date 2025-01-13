#include "HomeAssistantController.h"
#include "SecureSettings.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <exception>

HomeAssistantController::HomeAssistantController(QObject *parent)
    : QObject(parent)
    , network_manager(new QNetworkAccessManager(this))
    , is_connected(false)
    , resource_manager(nullptr)
    , update_timer(new QTimer(this))
{
    // Ensure the config directory exists
    SecureSettings::ensureConfigDirectory();
    
    // Initialize settings with the correct path
    settings = new QSettings(SecureSettings::getConfigPath(), QSettings::IniFormat);
    
    connect(network_manager, &QNetworkAccessManager::finished, this, &HomeAssistantController::handleNetworkReply);
    connect(update_timer, &QTimer::timeout, this, &HomeAssistantController::onUpdateTimer);

    // Load active devices from settings
    active_devices = QSet<QString>::fromList(settings->value("active_devices").toStringList());
}

HomeAssistantController::~HomeAssistantController()
{
    stopUpdateTimer();
    cleanupLights();
    delete settings;
}

void HomeAssistantController::cleanupLights()
{
    QStringList keys = lights.keys();
    for(const QString& key : keys)
    {
        HALightDevice* light = lights[key];
        if(light)
        {
            unregisterLight(light);
            delete light;
        }
    }
    lights.clear();
}

void HomeAssistantController::startUpdateTimer()
{
    if(!update_timer->isActive())
    {
        update_timer->start(5000); // Update every 5 seconds
    }
}

void HomeAssistantController::stopUpdateTimer()
{
    if(update_timer->isActive())
    {
        update_timer->stop();
    }
}

void HomeAssistantController::onUpdateTimer()
{
    if(is_connected)
    {
        DiscoverLights();
    }
}

bool HomeAssistantController::Connect(const QString& url, const QString& token)
{
    cleanupLights();
    
    base_url = url;
    if(!base_url.endsWith("/"))
        base_url += "/";
    
    auth_token = token;
    
    QNetworkRequest request(QUrl(base_url + "api/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + auth_token.toUtf8());
    
    network_manager->get(request);
    return true;
}

void HomeAssistantController::Disconnect()
{
    stopUpdateTimer();
    is_connected = false;
    emit connectionStatusChanged(false);
    cleanupLights();
}

bool HomeAssistantController::IsConnected() const
{
    return is_connected;
}

void HomeAssistantController::SaveSettings()
{
    settings->setValue("base_url", base_url);
    settings->setValue("auth_token", SecureSettings::encryptData(auth_token));
    settings->sync();
}

void HomeAssistantController::LoadSettings()
{
    base_url = settings->value("base_url").toString();
    auth_token = SecureSettings::decryptData(settings->value("auth_token").toString());

    if(!base_url.isEmpty() && !auth_token.isEmpty())
    {
        Connect(base_url, auth_token);
    }
}

void HomeAssistantController::handleNetworkReply(QNetworkReply* reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);

        QString endpoint = reply->url().path();
        
        // Only log non-standard endpoints
        if(!endpoint.endsWith("api/states") && 
           !endpoint.endsWith("turn_on") && 
           !endpoint.endsWith("turn_off"))
        {
            qDebug() << "[HomeAssistant] Response from:" << endpoint;
        }
        
        if(endpoint.endsWith("api/"))
        {
            if(!is_connected)
            {
                is_connected = true;
                emit connectionStatusChanged(true);
                startUpdateTimer();
                DiscoverLights();
            }
        }
        else if(endpoint.endsWith("api/states"))
        {
            QJsonArray states = doc.array();
            for(const QJsonValue &val : states)
            {
                QJsonObject state = val.toObject();
                QString entity_id = state["entity_id"].toString();
                
                if(entity_id.startsWith("light."))
                {
                    QJsonObject attributes = state["attributes"].toObject();
                    QString friendly_name = attributes["friendly_name"].toString();
                    
                    HALightDevice* light = nullptr;
                    if(lights.contains(entity_id))
                    {
                        light = lights[entity_id];
                    }
                    else
                    {
                        light = new HALightDevice(entity_id, friendly_name);
                        lights[entity_id] = light;
                        
                        if(active_devices.contains(entity_id))
                        {
                            registerLight(light);
                        }
                        
                        emit lightDiscovered(light);
                    }
                    
                    updateLightState(entity_id, attributes);
                }
            }
        }
    }
    else
    {
        qDebug() << "[HomeAssistant] Network error:" << reply->errorString();
        emit errorOccurred(reply->errorString());
        if(reply->error() == QNetworkReply::AuthenticationRequiredError)
        {
            Disconnect();
        }
    }

    reply->deleteLater();
}

void HomeAssistantController::updateLightState(const QString& entity_id, const QJsonObject& attributes)
{
    bool state = attributes["state"].toString() == "on";
    QJsonArray rgb_color = attributes["rgb_color"].toArray();
    int brightness = attributes["brightness"].toInt(255);
    
    QColor color;
    if(rgb_color.size() >= 3)
    {
        color = QColor(rgb_color[0].toInt(), rgb_color[1].toInt(), rgb_color[2].toInt());
    }
    else
    {
        color = QColor(255, 255, 255);
    }

    if(lights.contains(entity_id))
    {
        lights[entity_id]->UpdateState(state, color, brightness);
    }
}

void HomeAssistantController::onLightStateChangeRequested(const QString& entity_id, bool state, const QColor& color, int brightness)
{
    if(!is_connected) return;

    QJsonObject serviceData;
    serviceData["entity_id"] = entity_id;
    
    if(state)
    {
        serviceData["rgb_color"] = QJsonArray({color.red(), color.green(), color.blue()});
        serviceData["brightness"] = brightness;
        
        QNetworkRequest request(QUrl(base_url + "api/services/light/turn_on"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Authorization", "Bearer " + auth_token.toUtf8());
        
        network_manager->post(request, QJsonDocument(serviceData).toJson());
    }
    else
    {
        QNetworkRequest request(QUrl(base_url + "api/services/light/turn_off"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Authorization", "Bearer " + auth_token.toUtf8());
        
        network_manager->post(request, QJsonDocument(serviceData).toJson());
    }
}

void HomeAssistantController::DiscoverLights()
{
    if(!is_connected)
    {
        return;
    }

    QNetworkRequest request(QUrl(base_url + "api/states"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + auth_token.toUtf8());
    
    network_manager->get(request);
}

void HomeAssistantController::AddDevice(const QString& entity_id)
{
    if(!active_devices.contains(entity_id))
    {
        active_devices.insert(entity_id);
        SaveSettings();

        if(lights.contains(entity_id))
        {
            registerLight(lights[entity_id]);
        }
    }
}

void HomeAssistantController::RemoveDevice(const QString& entity_id)
{
    if(active_devices.contains(entity_id))
    {
        active_devices.remove(entity_id);
        SaveSettings();

        if(lights.contains(entity_id))
        {
            unregisterLight(lights[entity_id]);
        }
    }
}

QStringList HomeAssistantController::GetActiveDevices() const
{
    return active_devices.values();
}

void HomeAssistantController::SaveActiveDevices(const QStringList& devices)
{
    settings->setValue("active_devices", devices);
    settings->sync();
    active_devices = QSet<QString>::fromList(devices);
}

void HomeAssistantController::registerLight(HALightDevice* light)
{
    if(!light || !resource_manager)
    {
        return;
    }

    connect(light, &HALightDevice::lightStateChanged, 
            this, &HomeAssistantController::onLightStateChangeRequested,
            Qt::UniqueConnection);

    resource_manager->RegisterRGBController(light);
}

void HomeAssistantController::unregisterLight(HALightDevice* light)
{
    if(!light || !resource_manager)
    {
        return;
    }

    disconnect(light, &HALightDevice::lightStateChanged, 
              this, &HomeAssistantController::onLightStateChangeRequested);

    resource_manager->UnregisterRGBController(light);
}