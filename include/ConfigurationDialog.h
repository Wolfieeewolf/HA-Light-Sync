#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QWidget>
#include "HomeAssistantController.h"
#include "ui_ConfigurationDialog.h"

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(HomeAssistantController* controller, QWidget* parent = nullptr);
    ~ConfigurationDialog();

private slots:
    void onConnectClicked();
    void onRefreshClicked();
    void onAddSelectedClicked();
    void onRemoveSelectedClicked();
    void onLightDiscovered(HALightDevice* light);
    void onConnectionStatusChanged(bool connected);
    void onErrorOccurred(const QString& error);

private:
    Ui::ConfigurationDialog* ui;
    HomeAssistantController* controller;
    void loadSettings();
    void saveSettings();
    void updateStatus(const QString& message, bool error = false);
    bool isDeviceActive(const QString& entityId);
    void loadActiveDevices();
    void saveActiveDevices();
};

#endif // CONFIGURATIONDIALOG_H