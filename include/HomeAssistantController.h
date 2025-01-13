#ifndef HOMEASSISTANTCONTROLLER_H
#define HOMEASSISTANTCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include <QJsonDocument>
#include <QTimer>
#include "ResourceManager.h"
#include "HALightDevice.h"

class HomeAssistantController : public QObject
{
    Q_OBJECT

public:
    explicit HomeAssistantController(QObject *parent = nullptr);
    ~HomeAssistantController();

    bool Connect(const QString& url, const QString& token);
    void Disconnect();
    bool IsConnected() const;
    void DiscoverLights();
    void SaveSettings();
    void LoadSettings();

    QString GetBaseUrl() const { return base_url; }
    QString GetAuthToken() const { return auth_token; }

    void AddDevice(const QString& entity_id);
    void RemoveDevice(const QString& entity_id);
    QStringList GetActiveDevices() const;
    void SaveActiveDevices(const QStringList& devices);

    void SetResourceManager(ResourceManager* rm) { resource_manager = rm; }

signals:
    void lightDiscovered(HALightDevice* light);
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString& error);

private slots:
    void handleNetworkReply(QNetworkReply* reply);
    void updateLightState(const QString& entity_id, const QJsonObject& attributes);
    void onLightStateChangeRequested(const QString& entity_id, bool state, const QColor& color, int brightness);
    void onUpdateTimer();

private:
    void cleanupLights();
    void startUpdateTimer();
    void stopUpdateTimer();
    void registerLight(HALightDevice* light);
    void unregisterLight(HALightDevice* light);
    void sendRequest(const QString& endpoint, const QString& method = "GET", const QJsonDocument& data = QJsonDocument());

    QNetworkAccessManager* network_manager;
    QString base_url;
    QString auth_token;
    bool is_connected;
    QMap<QString, HALightDevice*> lights;
    QSet<QString> active_devices;
    QSettings* settings;
    ResourceManager* resource_manager;
    QTimer* update_timer;
};

#endif // HOMEASSISTANTCONTROLLER_H