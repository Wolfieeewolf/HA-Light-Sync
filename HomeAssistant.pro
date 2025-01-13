QT       += core gui network widgets

TARGET = "HA Light Sync"
TEMPLATE = lib
DEFINES += HOMEASSISTANT_LIBRARY

CONFIG += c++11 plugin qt

# Include the common plugin stuff
include(../OpenRGB.plugins.pri)

HEADERS += \
    ../../RGBController/RGBController.h \
    ../../Colors.h \
    include/HomeAssistantPlugin.h \
    include/HomeAssistantController.h \
    include/HALightDevice.h \
    include/ConfigurationDialog.h \
    include/SecureSettings.h

SOURCES += \
    ../../RGBController/RGBController.cpp \
    src/HomeAssistantPlugin.cpp \
    src/HomeAssistantController.cpp \
    src/HALightDevice.cpp \
    src/ConfigurationDialog.cpp \
    src/SecureSettings.cpp

FORMS += \
    forms/ConfigurationDialog.ui

INCLUDEPATH += \
    . \
    include \
    ../../ \
    ../../qt/ \
    ../../hidapi_wrapper \
    ../../SPDAccessor \
    ../../Controllers \
    ../../RGBController \
    ../../dependencies/hidapi \
    ../../dependencies/hidapi-win/include \
    ../../dependencies/json \
    ../../i2c_smbus \
    ../../i2c_tools \
    ../../net_port \
    generated_files

# Set the output directory to OpenRGB's plugins folder
PLUGIN_OUTPUT_DIR = $$shell_path($$(APPDATA)/OpenRGB/plugins)
DESTDIR = $$PLUGIN_OUTPUT_DIR

# If APPDATA environment variable is not set, try a default path
isEmpty(PLUGIN_OUTPUT_DIR) {
    DESTDIR = $$shell_path($$(USERPROFILE)/AppData/Roaming/OpenRGB/plugins)
}

# For debugging, print the destination directory
message("Plugin will be installed to: $$DESTDIR")

# Ignore warning about possible data loss
QMAKE_CXXFLAGS += -wd4267