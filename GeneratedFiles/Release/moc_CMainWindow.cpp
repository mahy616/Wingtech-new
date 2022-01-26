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
    QByteArrayData data[21];
    char stringdata0[259];
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
QT_MOC_LITERAL(7, 77, 15), // "OpenDataManager"
QT_MOC_LITERAL(8, 93, 19), // "ReceiveCameraStatus"
QT_MOC_LITERAL(9, 113, 12), // "e_CameraType"
QT_MOC_LITERAL(10, 126, 4), // "type"
QT_MOC_LITERAL(11, 131, 5), // "bOpen"
QT_MOC_LITERAL(12, 137, 16), // "ReceivePLCStatus"
QT_MOC_LITERAL(13, 154, 10), // "bConnected"
QT_MOC_LITERAL(14, 165, 16), // "ReceiveAlgoImage"
QT_MOC_LITERAL(15, 182, 11), // "s_ImageInfo"
QT_MOC_LITERAL(16, 194, 9), // "ImageInfo"
QT_MOC_LITERAL(17, 204, 7), // "isClean"
QT_MOC_LITERAL(18, 212, 22), // "ReceiveInitImageNumber"
QT_MOC_LITERAL(19, 235, 6), // "number"
QT_MOC_LITERAL(20, 242, 16) // "ReceiveStartSign"

    },
    "CMainWindow\0StartDection\0\0StopDection\0"
    "OpenSetting\0RecipeSetting\0AdminDection\0"
    "OpenDataManager\0ReceiveCameraStatus\0"
    "e_CameraType\0type\0bOpen\0ReceivePLCStatus\0"
    "bConnected\0ReceiveAlgoImage\0s_ImageInfo\0"
    "ImageInfo\0isClean\0ReceiveInitImageNumber\0"
    "number\0ReceiveStartSign"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    2,   75,    2, 0x08 /* Private */,
      12,    1,   80,    2, 0x08 /* Private */,
      14,    2,   83,    2, 0x08 /* Private */,
      18,    1,   88,    2, 0x08 /* Private */,
      20,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Bool,   10,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Bool,   16,   17,
    QMetaType::Void, QMetaType::Int,   19,
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
        case 5: _t->OpenDataManager(); break;
        case 6: _t->ReceiveCameraStatus((*reinterpret_cast< e_CameraType(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->ReceivePLCStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->ReceiveAlgoImage((*reinterpret_cast< s_ImageInfo(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: _t->ReceiveInitImageNumber((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->ReceiveStartSign(); break;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
