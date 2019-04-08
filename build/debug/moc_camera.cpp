/****************************************************************************
** Meta object code from reading C++ file 'camera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tetrix/camera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_camera_t {
    QByteArrayData data[7];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_camera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_camera_t qt_meta_stringdata_camera = {
    {
QT_MOC_LITERAL(0, 0, 6), // "camera"
QT_MOC_LITERAL(1, 7, 9), // "tourneCam"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 9), // "droiteCam"
QT_MOC_LITERAL(4, 28, 9), // "gaucheCam"
QT_MOC_LITERAL(5, 38, 13), // "updatePicture"
QT_MOC_LITERAL(6, 52, 12) // "positionMain"

    },
    "camera\0tourneCam\0\0droiteCam\0gaucheCam\0"
    "updatePicture\0positionMain"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_camera[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Char,

       0        // eod
};

void camera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        camera *_t = static_cast<camera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tourneCam(); break;
        case 1: _t->droiteCam(); break;
        case 2: _t->gaucheCam(); break;
        case 3: _t->updatePicture(); break;
        case 4: { char _r = _t->positionMain();
            if (_a[0]) *reinterpret_cast< char*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (camera::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&camera::tourneCam)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (camera::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&camera::droiteCam)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (camera::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&camera::gaucheCam)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject camera::staticMetaObject = { {
    &QLabel::staticMetaObject,
    qt_meta_stringdata_camera.data,
    qt_meta_data_camera,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *camera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *camera::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_camera.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int camera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void camera::tourneCam()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void camera::droiteCam()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void camera::gaucheCam()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
