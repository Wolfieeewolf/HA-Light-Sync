#include "ConfigurationDialog.h"
#include <QMessageBox>
#include <QDebug>

ConfigurationDialog::ConfigurationDialog(HomeAssistantController* controller, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ConfigurationDialog)
    , controller(controller)
{
    qDebug() << "[ConfigurationDialog] Creating dialog";
    
    try
    {
        ui->setupUi(this);

        if(!controller)
        {
            qDebug() << "[ConfigurationDialog] Invalid controller!";
            return;
        }

        // Set initial status text style
        ui->statusLabel->setStyleSheet("QLabel { color: red; }");

        // Connect signals/slots
        connect(ui->connectButton, &QPushButton::clicked, this, &ConfigurationDialog::onConnectClicked);
        connect(ui->refreshButton, &QPushButton::clicked, this, &ConfigurationDialog::onRefreshClicked);
        connect(ui->addSelectedButton, &QPushButton::clicked, this, &ConfigurationDialog::onAddSelectedClicked);
        connect(ui->removeButton, &QPushButton::clicked, this, &ConfigurationDialog::onRemoveSelectedClicked);
        
        connect(controller, &HomeAssistantController::lightDiscovered, 
                this, &ConfigurationDialog::onLightDiscovered, 
                Qt::QueuedConnection);
                
        connect(controller, &HomeAssistantController::connectionStatusChanged, 
                this, &ConfigurationDialog::onConnectionStatusChanged,
                Qt::QueuedConnection);
                
        connect(controller, &HomeAssistantController::errorOccurred, 
                this, &ConfigurationDialog::onErrorOccurred,
                Qt::QueuedConnection);

        // Load saved settings
        loadSettings();

        // Load active devices
        loadActiveDevices();

        qDebug() << "[ConfigurationDialog] Dialog created successfully";
    }
    catch(const std::exception& e)
    {
        qDebug() << "[ConfigurationDialog] Exception during construction:" << e.what();
    }
    catch(...)
    {
        qDebug() << "[ConfigurationDialog] Unknown exception during construction";
    }
}

ConfigurationDialog::~ConfigurationDialog()
{
    qDebug() << "[ConfigurationDialog] Destroying dialog";
    delete ui;
}

void ConfigurationDialog::onConnectClicked()
{
    qDebug() << "[ConfigurationDialog] Connect clicked";
    
    if(!controller) return;

    if(ui->urlEdit->text().isEmpty() || ui->tokenEdit->text().isEmpty())
    {
        ui->statusLabel->setText("Status: Please enter URL and token");
        ui->statusLabel->setStyleSheet("QLabel { color: red; }");
        return;
    }

    saveSettings();
    ui->statusLabel->setText("Status: Connecting...");
    ui->statusLabel->setStyleSheet("QLabel { color: orange; }");
    controller->Connect(ui->urlEdit->text(), ui->tokenEdit->text());
}

void ConfigurationDialog::onRefreshClicked()
{
    qDebug() << "[ConfigurationDialog] Refresh clicked";
    
    if(!controller) return;

    if(!controller->IsConnected())
    {
        ui->statusLabel->setText("Status: Not Connected");
        ui->statusLabel->setStyleSheet("QLabel { color: red; }");
        return;
    }
    controller->DiscoverLights();
}

void ConfigurationDialog::onAddSelectedClicked()
{
    qDebug() << "[ConfigurationDialog] Add Selected clicked";
    
    if(!controller) return;

    QList<QTreeWidgetItem*> items = ui->lightsList->selectedItems();
    if(items.isEmpty())
    {
        return;
    }

    for(QTreeWidgetItem* item : items)
    {
        if(!item) continue;

        QString entityId = item->text(1);
        if(entityId.isEmpty()) continue;

        if(!isDeviceActive(entityId))
        {
            QString displayName = item->text(0) + " (" + entityId + ")";
            ui->activeList->addItem(displayName);
            controller->AddDevice(entityId);
        }
    }
    saveActiveDevices();
}

void ConfigurationDialog::onRemoveSelectedClicked()
{
    qDebug() << "[ConfigurationDialog] Remove Selected clicked";
    
    if(!controller) return;

    QList<QListWidgetItem*> items = ui->activeList->selectedItems();
    if(items.isEmpty())
    {
        return;
    }

    for(QListWidgetItem* item : items)
    {
        if(!item) continue;

        QString text = item->text();
        int start = text.lastIndexOf("(") + 1;
        int end = text.lastIndexOf(")");
        if(start > 0 && end > start)
        {
            QString entityId = text.mid(start, end - start);
            if(!entityId.isEmpty())
            {
                controller->RemoveDevice(entityId);
                delete ui->activeList->takeItem(ui->activeList->row(item));
            }
        }
    }
    saveActiveDevices();
}

void ConfigurationDialog::onLightDiscovered(HALightDevice* light)
{
    qDebug() << "[ConfigurationDialog] Light discovered";
    
    if(!light) return;

    QString entityId = light->GetEntityId();
    if(entityId.isEmpty()) return;

    // Check if this light is already in the list
    QList<QTreeWidgetItem*> existingItems = ui->lightsList->findItems(entityId, Qt::MatchExactly, 1);
    if(existingItems.isEmpty())
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->lightsList);
        item->setText(0, QString::fromStdString(light->name));
        item->setText(1, entityId);
        ui->lightsList->addTopLevelItem(item);
    }
}

void ConfigurationDialog::onConnectionStatusChanged(bool connected)
{
    qDebug() << "[ConfigurationDialog] Connection status changed:" << connected;
    
    if(connected)
    {
        ui->statusLabel->setText("Status: Connected");
        ui->statusLabel->setStyleSheet("QLabel { color: green; }");
        if(controller) controller->DiscoverLights();
    }
    else
    {
        ui->statusLabel->setText("Status: Not Connected");
        ui->statusLabel->setStyleSheet("QLabel { color: red; }");
        ui->lightsList->clear();
    }
}

void ConfigurationDialog::onErrorOccurred(const QString& error)
{
    qDebug() << "[ConfigurationDialog] Error occurred:" << error;
    ui->statusLabel->setText("Status: Error - " + error);
    ui->statusLabel->setStyleSheet("QLabel { color: red; }");
}

void ConfigurationDialog::loadSettings()
{
    qDebug() << "[ConfigurationDialog] Loading settings";
    if(controller)
    {
        ui->urlEdit->setText(controller->GetBaseUrl());
        ui->tokenEdit->setText(controller->GetAuthToken());

        // If we have settings, try to connect
        if(!ui->urlEdit->text().isEmpty() && !ui->tokenEdit->text().isEmpty())
        {
            controller->Connect(ui->urlEdit->text(), ui->tokenEdit->text());
        }
    }
}

void ConfigurationDialog::saveSettings()
{
    qDebug() << "[ConfigurationDialog] Saving settings";
    if(controller)
    {
        controller->SaveSettings();
    }
}

void ConfigurationDialog::saveActiveDevices()
{
    qDebug() << "[ConfigurationDialog] Saving active devices";
    if(!controller) return;

    QStringList devices;
    for(int i = 0; i < ui->activeList->count(); i++)
    {
        QListWidgetItem* item = ui->activeList->item(i);
        if(!item) continue;

        QString text = item->text();
        int start = text.lastIndexOf("(") + 1;
        int end = text.lastIndexOf(")");
        if(start > 0 && end > start)
        {
            QString entityId = text.mid(start, end - start);
            if(!entityId.isEmpty())
            {
                devices.append(entityId);
            }
        }
    }
    controller->SaveActiveDevices(devices);
}

void ConfigurationDialog::loadActiveDevices()
{
    qDebug() << "[ConfigurationDialog] Loading active devices";
    if(!controller) return;

    ui->activeList->clear();
    QStringList devices = controller->GetActiveDevices();
    for(const QString& deviceId : devices)
    {
        if(!deviceId.isEmpty())
        {
            // Try to find the device name from the lights list
            QString displayName = deviceId;
            QList<QTreeWidgetItem*> items = ui->lightsList->findItems(deviceId, Qt::MatchExactly, 1);
            if(!items.isEmpty() && items.first())
            {
                displayName = items.first()->text(0) + " (" + deviceId + ")";
            }
            ui->activeList->addItem(displayName);
        }
    }
}

bool ConfigurationDialog::isDeviceActive(const QString& entityId)
{
    if(entityId.isEmpty()) return false;

    for(int i = 0; i < ui->activeList->count(); i++)
    {
        QListWidgetItem* item = ui->activeList->item(i);
        if(!item) continue;

        QString text = item->text();
        if(text.contains("(" + entityId + ")"))
        {
            return true;
        }
    }
    return false;
}