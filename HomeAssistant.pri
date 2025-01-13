INCLUDEPATH += $$PWD/include
HEADERS += \
    $$PWD/include/HomeAssistantPlugin.h \
    $$PWD/include/HomeAssistantController.h \
    $$PWD/include/HALightDevice.h \
    $$PWD/include/SecureSettings.h

SOURCES += \
    $$PWD/src/HomeAssistantPlugin.cpp \
    $$PWD/src/HomeAssistantController.cpp \
    $$PWD/src/HALightDevice.cpp \
    $$PWD/src/SecureSettings.cpp

FORMS += \
    $$PWD/forms/ConfigurationDialog.ui

RESOURCES += \
    $$PWD/resources/resources.qrc