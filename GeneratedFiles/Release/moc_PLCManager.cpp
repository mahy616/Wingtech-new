/****************************************************************************
** Meta object code from reading C++ file 'PLCManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../PLCManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PLCManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CPLCManager_t {
    QByteArrayData data[17];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPLCManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPLCManager_t qt_meta_stringdata_CPLCManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CPLCManager"
QT_MOC_LITERAL(1, 12, 17), // "SendConnectStatus"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "status"
QT_MOC_LITERAL(4, 38, 14), // "SendPLCMessage"
QT_MOC_LITERAL(5, 53, 3), // "msg"
QT_MOC_LITERAL(6, 57, 19), // "SendChangePLCRecipe"
QT_MOC_LITERAL(7, 77, 6), // "number"
QT_MOC_LITERAL(8, 84, 11), // "ImageCounts"
QT_MOC_LITERAL(9, 96, 17), // "SendSavePLCRecipe"
QT_MOC_LITERAL(10, 114, 13), // "SendStartSign"
QT_MOC_LITERAL(11, 128, 16), // "SendRefreshIndex"
QT_MOC_LITERAL(12, 145, 14), // "SendPartNumber"
QT_MOC_LITERAL(13, 160, 5), // "index"
QT_MOC_LITERAL(14, 166, 13), // "SlotTimeOuter"
QT_MOC_LITERAL(15, 180, 17), // "SlotTimeOuterRead"
QT_MOC_LITERAL(16, 198, 11) // "ReadPLCData"

    },
    "CPLCManager\0SendConnectStatus\0\0status\0"
    "SendPLCMessage\0msg\0SendChangePLCRecipe\0"
    "number\0ImageCounts\0SendSavePLCRecipe\0"
    "SendStartSign\0SendRefreshIndex\0"
    "SendPartNumber\0index\0SlotTimeOuter\0"
    "SlotTimeOuterRead\0ReadPLCData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPLCManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    3,   70,    2, 0x06 /* Public */,
       9,    3,   77,    2, 0x06 /* Public */,
      10,    0,   84,    2, 0x06 /* Public */,
      11,    0,   85,    2, 0x06 /* Public */,
      12,    2,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   91,    2, 0x08 /* Private */,
      15,    0,   92,    2, 0x08 /* Private */,
      16,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    5,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    5,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,   13,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CPLCManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CPLCManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendConnectStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->SendPLCMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->SendChangePLCRecipe((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->SendSavePLCRecipe((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->SendStartSign(); break;
        case 5: _t->SendRefreshIndex(); break;
        case 6: _t->SendPartNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->SlotTimeOuter(); break;
        case 8: _t->SlotTimeOuterRead(); break;
        case 9: _t->ReadPLCData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CPLCManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPLCManager::SendConnectStatus)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CPLCManager::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPLCManager::SendPLCMessage)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CPLCManager::*)(QString , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPLCManager::SendChangePLCRecipe)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CPLCManager::*)(QString , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPLCManager::SendSavePLCRecipe)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CPLCManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPLCManager::SendStartSign)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CPLCManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPLCManager::SendRefreshIndex)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CPLCManager::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPLCManager::SendPartNumber)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CPLCManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CPLCManager.data,
    qt_meta_data_CPLCManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CPLCManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPLCManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CPLCManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CPLCManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void CPLCManager::SendConnectStatus(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CPLCManager::SendPLCMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CPLCManager::SendChangePLCRecipe(QString _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CPLCManager::SendSavePLCRecipe(QString _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CPLCManager::SendStartSign()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CPLCManager::SendRefreshIndex()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CPLCManager::SendPartNumber(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
