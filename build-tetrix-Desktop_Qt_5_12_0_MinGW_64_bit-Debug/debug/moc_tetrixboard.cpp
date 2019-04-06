/****************************************************************************
** Meta object code from reading C++ file 'tetrixboard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tetrix/tetrixboard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tetrixboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TetrixBoard_t {
    QByteArrayData data[12];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TetrixBoard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TetrixBoard_t qt_meta_stringdata_TetrixBoard = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TetrixBoard"
QT_MOC_LITERAL(1, 12, 12), // "scoreChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "score"
QT_MOC_LITERAL(4, 32, 12), // "levelChanged"
QT_MOC_LITERAL(5, 45, 5), // "level"
QT_MOC_LITERAL(6, 51, 19), // "linesRemovedChanged"
QT_MOC_LITERAL(7, 71, 8), // "numLines"
QT_MOC_LITERAL(8, 80, 5), // "start"
QT_MOC_LITERAL(9, 86, 5), // "pause"
QT_MOC_LITERAL(10, 92, 13), // "updatePicture"
QT_MOC_LITERAL(11, 106, 12) // "positionMain"

    },
    "TetrixBoard\0scoreChanged\0\0score\0"
    "levelChanged\0level\0linesRemovedChanged\0"
    "numLines\0start\0pause\0updatePicture\0"
    "positionMain"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TetrixBoard[] = {

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
       4,    1,   52,    2, 0x06 /* Public */,
       6,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   58,    2, 0x0a /* Public */,
       9,    0,   59,    2, 0x0a /* Public */,
      10,    0,   60,    2, 0x0a /* Public */,
      11,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TetrixBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TetrixBoard *_t = static_cast<TetrixBoard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->scoreChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->levelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->linesRemovedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->start(); break;
        case 4: _t->pause(); break;
        case 5: _t->updatePicture(); break;
        case 6: _t->positionMain(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TetrixBoard::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TetrixBoard::scoreChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TetrixBoard::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TetrixBoard::levelChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TetrixBoard::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TetrixBoard::linesRemovedChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TetrixBoard::staticMetaObject = { {
    &QGLWidget::staticMetaObject,
    qt_meta_stringdata_TetrixBoard.data,
    qt_meta_data_TetrixBoard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TetrixBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TetrixBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TetrixBoard.stringdata0))
        return static_cast<void*>(this);
    return QGLWidget::qt_metacast(_clname);
}

int TetrixBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TetrixBoard::scoreChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TetrixBoard::levelChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TetrixBoard::linesRemovedChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
