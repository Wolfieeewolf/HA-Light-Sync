#include "HomeAssistantPlugin.h"
#include "ConfigurationDialog.h"
#include <QDialog>
#include <QDebug>

HomeAssistantPlugin::HomeAssistantPlugin():
    QObject(),
    controller(nullptr),
    dark_theme(false),
    resource_manager(nullptr),
    config_widget(nullptr)
{
    qDebug() << "[HALightSync] Plugin constructor called";
}

HomeAssistantPlugin::~HomeAssistantPlugin()
{
    qDebug() << "[HALightSync] Plugin destructor called";
    if(controller)
    {
        try 
        {
            controller->SaveSettings();
            controller->Disconnect();
            delete controller;
            controller = nullptr;
        }
        catch(...)
        {
            qDebug() << "[HALightSync] Error during plugin cleanup";
        }
    }

    if(config_widget)
    {
        delete config_widget;
        config_widget = nullptr;
    }
}

OpenRGBPluginInfo HomeAssistantPlugin::GetPluginInfo()
{
    OpenRGBPluginInfo info;
    info.Name = "HA Light Sync";
    info.Description = "Synchronizes RGB lighting with Home Assistant";
    info.Version = "1.1";
    info.Location = OPENRGB_PLUGIN_LOCATION_SETTINGS;
    info.Label = "HA Light Sync";
    return info;
}

unsigned int HomeAssistantPlugin::GetPluginAPIVersion()
{
    return OPENRGB_PLUGIN_API_VERSION;
}

void HomeAssistantPlugin::Load(bool dark, ResourceManager* rm)
{
    qDebug() << "[HALightSync] Plugin Load called";
    
    try
    {
        dark_theme = dark;
        resource_manager = rm;

        if(controller)
        {
            qDebug() << "[HALightSync] Controller already exists, cleaning up";
            controller->SaveSettings();
            controller->Disconnect();
            delete controller;
            controller = nullptr;
        }

        qDebug() << "[HALightSync] Creating new controller";
        controller = new HomeAssistantController(this);
        
        if(!controller)
        {
            qDebug() << "[HALightSync] Failed to create controller";
            return;
        }

        qDebug() << "[HALightSync] Setting resource manager";
        controller->SetResourceManager(rm);

        qDebug() << "[HALightSync] Loading settings";
        controller->LoadSettings();
        
        qDebug() << "[HALightSync] Plugin Load completed";
    }
    catch(const std::exception& e)
    {
        qDebug() << "[HALightSync] Exception during Load:" << e.what();
    }
    catch(...)
    {
        qDebug() << "[HALightSync] Unknown exception during Load";
    }
}

QWidget* HomeAssistantPlugin::GetWidget()
{
    qDebug() << "[HALightSync] GetWidget called";
    
    try
    {
        if(!config_widget && controller)
        {
            qDebug() << "[HALightSync] Creating configuration widget";
            config_widget = new ConfigurationDialog(controller);
        }
        return config_widget;
    }
    catch(const std::exception& e)
    {
        qDebug() << "[HALightSync] Exception in GetWidget:" << e.what();
        return nullptr;
    }
    catch(...)
    {
        qDebug() << "[HALightSync] Unknown exception in GetWidget";
        return nullptr;
    }
}

QMenu* HomeAssistantPlugin::GetTrayMenu()
{
    return nullptr;
}

void HomeAssistantPlugin::Unload()
{
    qDebug() << "[HALightSync] Plugin Unload called";
    
    try
    {
        if(controller)
        {
            qDebug() << "[HALightSync] Saving settings and disconnecting";
            controller->SaveSettings();
            controller->Disconnect();
        }
    }
    catch(const std::exception& e)
    {
        qDebug() << "[HALightSync] Exception during Unload:" << e.what();
    }
    catch(...)
    {
        qDebug() << "[HALightSync] Unknown exception during Unload";
    }
}