#ifndef HOMEASSISTANTPLUGIN_H
#define HOMEASSISTANTPLUGIN_H

#include "OpenRGBPluginInterface.h"
#include "ResourceManager.h"
#include "HomeAssistantController.h"
#include "ConfigurationDialog.h"

class HomeAssistantPlugin : public QObject, public OpenRGBPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.OpenRGB.HomeAssistantPlugin")
    Q_INTERFACES(OpenRGBPluginInterface)

public:
    HomeAssistantPlugin();
    ~HomeAssistantPlugin();

    // Interface implementations
    OpenRGBPluginInfo   GetPluginInfo() override;
    unsigned int        GetPluginAPIVersion() override;
    void                Load(bool dark_theme, ResourceManager* resource_manager) override;
    QWidget*            GetWidget() override;
    QMenu*             GetTrayMenu() override;
    void                Unload() override;

private:
    HomeAssistantController*    controller;
    bool                        dark_theme;
    ResourceManager*            resource_manager;
    ConfigurationDialog*        config_widget;
};

#endif // HOMEASSISTANTPLUGIN_H