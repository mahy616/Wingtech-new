/****************************************************************************
** Meta object code from reading C++ file 'CRecipeManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CRecipeManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CRecipeManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CRecipeManager_t {
    QByteArrayData data[39];
    char stringdata0[528];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CRecipeManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CRecipeManager_t qt_meta_stringdata_CRecipeManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CRecipeManager"
QT_MOC_LITERAL(1, 15, 13), // "SendStartSign"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 20), // "SendCameraParameters"
QT_MOC_LITERAL(4, 51, 26), // "QVector<QVector<QString> >"
QT_MOC_LITERAL(5, 78, 19), // "AllCameraParameters"
QT_MOC_LITERAL(6, 98, 19), // "SendLoadRenderImage"
QT_MOC_LITERAL(7, 118, 3), // "Mat"
QT_MOC_LITERAL(8, 122, 5), // "image"
QT_MOC_LITERAL(9, 128, 1), // "e"
QT_MOC_LITERAL(10, 130, 4), // "time"
QT_MOC_LITERAL(11, 135, 23), // "SendAlgoImageFromRecipe"
QT_MOC_LITERAL(12, 159, 11), // "s_ImageInfo"
QT_MOC_LITERAL(13, 171, 9), // "ImageInfo"
QT_MOC_LITERAL(14, 181, 7), // "isClean"
QT_MOC_LITERAL(15, 189, 12), // "SwitchRecipe"
QT_MOC_LITERAL(16, 202, 4), // "Name"
QT_MOC_LITERAL(17, 207, 10), // "SaveRecipe"
QT_MOC_LITERAL(18, 218, 12), // "RemoveRecipe"
QT_MOC_LITERAL(19, 231, 15), // "BrowseModelPath"
QT_MOC_LITERAL(20, 247, 20), // "ReceiveSavePlcRecipe"
QT_MOC_LITERAL(21, 268, 3), // "msg"
QT_MOC_LITERAL(22, 272, 6), // "number"
QT_MOC_LITERAL(23, 279, 11), // "ImageCounts"
QT_MOC_LITERAL(24, 291, 22), // "ReceiveChangePlcRecipe"
QT_MOC_LITERAL(25, 314, 20), // "ReceivaOriginalImage"
QT_MOC_LITERAL(26, 335, 5), // "Image"
QT_MOC_LITERAL(27, 341, 7), // "ImageID"
QT_MOC_LITERAL(28, 349, 12), // "e_CameraType"
QT_MOC_LITERAL(29, 362, 4), // "Type"
QT_MOC_LITERAL(30, 367, 16), // "ReceivaAlgoImage"
QT_MOC_LITERAL(31, 384, 16), // "ReceiveStartSign"
QT_MOC_LITERAL(32, 401, 20), // "ReceiveAlgoThreshold"
QT_MOC_LITERAL(33, 422, 11), // "vector<int>"
QT_MOC_LITERAL(34, 434, 18), // "AlgoThresholdZheng"
QT_MOC_LITERAL(35, 453, 15), // "AlgoThresholdCe"
QT_MOC_LITERAL(36, 469, 27), // "ReceiveOffLineAlgoThreshold"
QT_MOC_LITERAL(37, 497, 13), // "AlgoThreshold"
QT_MOC_LITERAL(38, 511, 16) // "ReceiveLoadImage"

    },
    "CRecipeManager\0SendStartSign\0\0"
    "SendCameraParameters\0QVector<QVector<QString> >\0"
    "AllCameraParameters\0SendLoadRenderImage\0"
    "Mat\0image\0e\0time\0SendAlgoImageFromRecipe\0"
    "s_ImageInfo\0ImageInfo\0isClean\0"
    "SwitchRecipe\0Name\0SaveRecipe\0RemoveRecipe\0"
    "BrowseModelPath\0ReceiveSavePlcRecipe\0"
    "msg\0number\0ImageCounts\0ReceiveChangePlcRecipe\0"
    "ReceivaOriginalImage\0Image\0ImageID\0"
    "e_CameraType\0Type\0ReceivaAlgoImage\0"
    "ReceiveStartSign\0ReceiveAlgoThreshold\0"
    "vector<int>\0AlgoThresholdZheng\0"
    "AlgoThresholdCe\0ReceiveOffLineAlgoThreshold\0"
    "AlgoThreshold\0ReceiveLoadImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CRecipeManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    1,   95,    2, 0x06 /* Public */,
       6,    3,   98,    2, 0x06 /* Public */,
      11,    2,  105,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    1,  110,    2, 0x08 /* Private */,
      17,    0,  113,    2, 0x08 /* Private */,
      18,    0,  114,    2, 0x08 /* Private */,
      19,    0,  115,    2, 0x08 /* Private */,
      20,    3,  116,    2, 0x08 /* Private */,
      24,    3,  123,    2, 0x08 /* Private */,
      25,    3,  130,    2, 0x08 /* Private */,
      30,    1,  137,    2, 0x08 /* Private */,
      31,    0,  140,    2, 0x08 /* Private */,
      32,    2,  141,    2, 0x08 /* Private */,
      36,    1,  146,    2, 0x08 /* Private */,
      38,    2,  149,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool, QMetaType::Int,    8,    9,   10,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Bool,   13,   14,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,   21,   22,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,   21,   22,   23,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int, 0x80000000 | 28,   26,   27,   29,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 33, 0x80000000 | 33,   34,   35,
    QMetaType::Void, 0x80000000 | 33,   37,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool,    8,    9,

       0        // eod
};

void CRecipeManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CRecipeManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendStartSign(); break;
        case 1: _t->SendCameraParameters((*reinterpret_cast< QVector<QVector<QString> >(*)>(_a[1]))); break;
        case 2: _t->SendLoadRenderImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->SendAlgoImageFromRecipe((*reinterpret_cast< s_ImageInfo(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->SwitchRecipe((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->SaveRecipe(); break;
        case 6: _t->RemoveRecipe(); break;
        case 7: _t->BrowseModelPath(); break;
        case 8: _t->ReceiveSavePlcRecipe((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->ReceiveChangePlcRecipe((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 10: _t->ReceivaOriginalImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< e_CameraType(*)>(_a[3]))); break;
        case 11: _t->ReceivaAlgoImage((*reinterpret_cast< s_ImageInfo(*)>(_a[1]))); break;
        case 12: _t->ReceiveStartSign(); break;
        case 13: _t->ReceiveAlgoThreshold((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< vector<int>(*)>(_a[2]))); break;
        case 14: _t->ReceiveOffLineAlgoThreshold((*reinterpret_cast< vector<int>(*)>(_a[1]))); break;
        case 15: _t->ReceiveLoadImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<QString> > >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CRecipeManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRecipeManager::SendStartSign)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CRecipeManager::*)(QVector<QVector<QString>> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRecipeManager::SendCameraParameters)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CRecipeManager::*)(Mat , bool , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRecipeManager::SendLoadRenderImage)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CRecipeManager::*)(s_ImageInfo , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRecipeManager::SendAlgoImageFromRecipe)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CRecipeManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CRecipeManager.data,
    qt_meta_data_CRecipeManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CRecipeManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CRecipeManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CRecipeManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CRecipeManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void CRecipeManager::SendStartSign()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CRecipeManager::SendCameraParameters(QVector<QVector<QString>> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CRecipeManager::SendLoadRenderImage(Mat _t1, bool _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CRecipeManager::SendAlgoImageFromRecipe(s_ImageInfo _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
