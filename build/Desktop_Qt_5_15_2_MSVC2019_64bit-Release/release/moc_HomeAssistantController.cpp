/****************************************************************************
** Meta object code from reading C++ file 'HomeAssistantController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/HomeAssistantController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HomeAssistantController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HomeAssistantController_t {
    QByteArrayData data[20];
    char stringdata0[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HomeAssistantController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HomeAssistantController_t qt_meta_stringdata_HomeAssistantController = {
    {
QT_MOC_LITERAL(0, 0, 23), // "HomeAssistantController"
QT_MOC_LITERAL(1, 24, 15), // "lightDiscovered"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 14), // "HALightDevice*"
QT_MOC_LITERAL(4, 56, 5), // "light"
QT_MOC_LITERAL(5, 62, 23), // "connectionStatusChanged"
QT_MOC_LITERAL(6, 86, 9), // "connected"
QT_MOC_LITERAL(7, 96, 13), // "errorOccurred"
QT_MOC_LITERAL(8, 110, 5), // "error"
QT_MOC_LITERAL(9, 116, 18), // "handleNetworkReply"
QT_MOC_LITERAL(10, 135, 14), // "QNetworkReply*"
QT_MOC_LITERAL(11, 150, 5), // "reply"
QT_MOC_LITERAL(12, 156, 16), // "updateLightState"
QT_MOC_LITERAL(13, 173, 9), // "entity_id"
QT_MOC_LITERAL(14, 183, 10), // "attributes"
QT_MOC_LITERAL(15, 194, 27), // "onLightStateChangeRequested"
QT_MOC_LITERAL(16, 222, 5), // "state"
QT_MOC_LITERAL(17, 228, 5), // "color"
QT_MOC_LITERAL(18, 234, 10), // "brightness"
QT_MOC_LITERAL(19, 245, 13) // "onUpdateTimer"

    },
    "HomeAssistantController\0lightDiscovered\0"
    "\0HALightDevice*\0light\0connectionStatusChanged\0"
    "connected\0errorOccurred\0error\0"
    "handleNetworkReply\0QNetworkReply*\0"
    "reply\0updateLightState\0entity_id\0"
    "attributes\0onLightStateChangeRequested\0"
    "state\0color\0brightness\0onUpdateTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HomeAssistantController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    1,   52,    2, 0x06 /* Public */,
       7,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   58,    2, 0x08 /* Private */,
      12,    2,   61,    2, 0x08 /* Private */,
      15,    4,   66,    2, 0x08 /* Private */,
      19,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   13,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::QColor, QMetaType::Int,   13,   16,   17,   18,
    QMetaType::Void,

       0        // eod
};

void HomeAssistantController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HomeAssistantController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lightDiscovered((*reinterpret_cast< HALightDevice*(*)>(_a[1]))); break;
        case 1: _t->connectionStatusChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->handleNetworkReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->updateLightState((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QJsonObject(*)>(_a[2]))); break;
        case 5: _t->onLightStateChangeRequested((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QColor(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 6: _t->onUpdateTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< HALightDevice* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HomeAssistantController::*)(HALightDevice * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HomeAssistantController::lightDiscovered)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HomeAssistantController::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HomeAssistantController::connectionStatusChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (HomeAssistantController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HomeAssistantController::errorOccurred)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HomeAssistantController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_HomeAssistantController.data,
    qt_meta_data_HomeAssistantController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HomeAssistantController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HomeAssistantController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HomeAssistantController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HomeAssistantController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void HomeAssistantController::lightDiscovered(HALightDevice * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HomeAssistantController::connectionStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HomeAssistantController::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
