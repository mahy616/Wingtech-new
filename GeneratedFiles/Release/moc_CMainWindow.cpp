/****************************************************************************
** Meta object code from reading C++ file 'CMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CMainWindow_t {
    QByteArrayData data[20];
    char stringdata0[243];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMainWindow_t qt_meta_stringdata_CMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CMainWindow"
QT_MOC_LITERAL(1, 12, 12), // "StartDection"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "StopDection"
QT_MOC_LITERAL(4, 38, 11), // "OpenSetting"
QT_MOC_LITERAL(5, 50, 13), // "RecipeSetting"
QT_MOC_LITERAL(6, 64, 12), // "AdminDection"
QT_MOC_LITERAL(7, 77, 19), // "ReceiveCameraStatus"
QT_MOC_LITERAL(8, 97, 12), // "e_CameraType"
QT_MOC_LITERAL(9, 110, 4), // "type"
QT_MOC_LITERAL(10, 115, 5), // "bOpen"
QT_MOC_LITERAL(11, 121, 16), // "ReceivePLCStatus"
QT_MOC_LITERAL(12, 138, 10), // "bConnected"
QT_MOC_LITERAL(13, 149, 16), // "ReceiveAlgoImage"
QT_MOC_LITERAL(14, 166, 11), // "s_ImageInfo"
QT_MOC_LITERAL(15, 178, 9), // "ImageInfo"
QT_MOC_LITERAL(16, 188, 7), // "isClean"
QT_MOC_LITERAL(17, 196, 22), // "ReceiveInitImageNumber"
QT_MOC_LITERAL(18, 219, 6), // "number"
QT_MOC_LITERAL(19, 226, 16) // "ReceiveStartSign"

    },
    "CMainWindow\0StartDection\0\0StopDection\0"
    "OpenSetting\0RecipeSetting\0AdminDection\0"
    "ReceiveCameraStatus\0e_CameraType\0type\0"
    "bOpen\0ReceivePLCStatus\0bConnected\0"
    "ReceiveAlgoImage\0s_ImageInfo\0ImageInfo\0"
    "isClean\0ReceiveInitImageNumber\0number\0"
    "ReceiveStartSign"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    2,   69,    2, 0x08 /* Private */,
      11,    1,   74,    2, 0x08 /* Private */,
      13,    2,   77,    2, 0x08 /* Private */,
      17,    1,   82,    2, 0x08 /* Private */,
      19,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Bool,    9,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Bool,   15,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,

       0        // eod
};

void CMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->StartDection(); break;
        case 1: _t->StopDection(); break;
        case 2: _t->OpenSetting(); break;
        case 3: _t->RecipeSetting(); break;
        case 4: _t->AdminDection(); break;
        case 5: _t->ReceiveCameraStatus((*reinterpret_cast< e_CameraType(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->ReceivePLCStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->ReceiveAlgoImage((*reinterpret_cast< s_ImageInfo(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->ReceiveInitImageNumber((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->ReceiveStartSign(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CMainWindow.data,
    qt_meta_data_CMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
