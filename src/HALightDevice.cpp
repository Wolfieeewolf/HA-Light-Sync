#include "HALightDevice.h"
#include <QDebug>

HALightDevice::HALightDevice(const QString& entity_id, const QString& friendly_name) :
    RGBController(),
    entity_id(entity_id),
    is_on(false),
    brightness(255)
{
    name        = friendly_name.toStdString();
    vendor      = "Home Assistant";
    type        = DEVICE_TYPE_LIGHT;
    description = "Home Assistant Light Device";
    
    current_color = QColor(255, 255, 255);

    mode Direct;
    Direct.name       = "Direct";
    Direct.value      = 0;
    Direct.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    Direct.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Direct);

    SetupZones();
}

HALightDevice::~HALightDevice()
{
}

void HALightDevice::SetupZones()
{
    zone led_zone;
    led_zone.name          = name;
    led_zone.type          = ZONE_TYPE_SINGLE;
    led_zone.leds_min      = 1;
    led_zone.leds_max      = 1;
    led_zone.leds_count    = 1;
    led_zone.matrix_map    = NULL;
    zones.push_back(led_zone);

    led new_led;
    new_led.name = name;
    leds.push_back(new_led);

    SetupColors();
}

void HALightDevice::ResizeZone(int /*zone*/, int /*new_size*/)
{
    // Not implemented - single LED only
}

void HALightDevice::DeviceUpdateLEDs()
{
    if(colors.size() > 0)
    {
        QColor new_color = QColor(RGBGetRValue(colors[0]), 
                                RGBGetGValue(colors[0]), 
                                RGBGetBValue(colors[0]));
        
        if(new_color != current_color || colors[0] == 0)
        {
            current_color = new_color;
            is_on = (colors[0] != 0);
            emit lightStateChanged(entity_id, is_on, current_color, brightness);
        }
    }
}

void HALightDevice::UpdateZoneLEDs(int /*zone*/)
{
    DeviceUpdateLEDs();
}

void HALightDevice::UpdateSingleLED(int /*led*/)
{
    DeviceUpdateLEDs();
}

void HALightDevice::SetCustomMode()
{
    // Not implemented - using direct mode only
}

void HALightDevice::DeviceUpdateMode()
{
    // Not implemented - using direct mode only
}

void HALightDevice::UpdateState(bool state, const QColor& color, int new_brightness)
{
    // Only log significant state changes
    if(state != is_on || color != current_color || brightness != new_brightness)
    {
        qDebug() << "[HomeAssistant] State change for" << entity_id 
                 << "- Power:" << (state ? "On" : "Off")
                 << "Color:" << color
                 << "Brightness:" << new_brightness;
    }

    is_on = state;
    current_color = color;
    brightness = new_brightness;

    if(colors.size() > 0)
    {
        if(state)
        {
            colors[0] = ToRGBColor(current_color.red(), 
                                 current_color.green(), 
                                 current_color.blue());
        }
        else
        {
            colors[0] = 0;
        }
    }
}