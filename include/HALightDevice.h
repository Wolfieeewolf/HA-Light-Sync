#ifndef HALIGHTDEVICE_H
#define HALIGHTDEVICE_H

#include "RGBController.h"
#include <QString>
#include <QColor>
#include <QObject>

class HALightDevice : public QObject, public RGBController
{
    Q_OBJECT

public:
    HALightDevice(const QString& entity_id, const QString& friendly_name);
    ~HALightDevice();

    // Required implementations from RGBController
    void        SetupZones() override;
    void        ResizeZone(int zone, int new_size) override;
    void        DeviceUpdateLEDs() override;
    void        UpdateZoneLEDs(int zone) override;
    void        UpdateSingleLED(int led) override;
    void        SetCustomMode() override;
    void        DeviceUpdateMode() override;

    // Home Assistant specific functionality
    void UpdateState(bool state, const QColor& color, int brightness);
    QString GetEntityId() const { return entity_id; }

signals:
    void lightStateChanged(const QString& entity_id, bool state, const QColor& color, int brightness);

private:
    QString entity_id;
    QString friendly_name;
    bool is_on;
    QColor current_color;
    int brightness;
};

Q_DECLARE_METATYPE(HALightDevice*)

#endif // HALIGHTDEVICE_H