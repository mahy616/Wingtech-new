/****************************************************************************
** Meta object code from reading C++ file 'ImageCapture.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ImageCapture.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageCapture.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CImageCapture_t {
    QByteArrayData data[16];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CImageCapture_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CImageCapture_t qt_meta_stringdata_CImageCapture = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CImageCapture"
QT_MOC_LITERAL(1, 14, 15), // "SendCameraImage"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3), // "Mat"
QT_MOC_LITERAL(4, 35, 5), // "image"
QT_MOC_LITERAL(5, 41, 12), // "e_CameraType"
QT_MOC_LITERAL(6, 54, 6), // "m_Type"
QT_MOC_LITERAL(7, 61, 1), // "m"
QT_MOC_LITERAL(8, 63, 5), // "index"
QT_MOC_LITERAL(9, 69, 13), // "SendAlgoImage"
QT_MOC_LITERAL(10, 83, 13), // "OriginalImage"
QT_MOC_LITERAL(11, 97, 11), // "RenderImage"
QT_MOC_LITERAL(12, 109, 3), // "bok"
QT_MOC_LITERAL(13, 113, 15), // "SendImageToAlgo"
QT_MOC_LITERAL(14, 129, 4), // "type"
QT_MOC_LITERAL(15, 134, 14) // "SendImageIndex"

    },
    "CImageCapture\0SendCameraImage\0\0Mat\0"
    "image\0e_CameraType\0m_Type\0m\0index\0"
    "SendAlgoImage\0OriginalImage\0RenderImage\0"
    "bok\0SendImageToAlgo\0type\0SendImageIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CImageCapture[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   34,    2, 0x06 /* Public */,
       9,    4,   43,    2, 0x06 /* Public */,
      13,    3,   52,    2, 0x06 /* Public */,
      15,    1,   59,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::Int, QMetaType::Int,    4,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::Int, QMetaType::Bool,   10,   11,    8,   12,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::Int,   10,   14,    8,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void CImageCapture::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CImageCapture *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendCameraImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< e_CameraType(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->SendAlgoImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< e_CameraType(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 2: _t->SendImageToAlgo((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< e_CameraType(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->SendImageIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CImageCapture::*)(Mat , e_CameraType , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CImageCapture::SendCameraImage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CImageCapture::*)(Mat , e_CameraType , int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CImageCapture::SendAlgoImage)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CImageCapture::*)(Mat , e_CameraType , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CImageCapture::SendImageToAlgo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CImageCapture::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CImageCapture::SendImageIndex)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CImageCapture::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_CImageCapture.data,
    qt_meta_data_CImageCapture,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CImageCapture::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CImageCapture::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CImageCapture.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int CImageCapture::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CImageCapture::SendCameraImage(Mat _t1, e_CameraType _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CImageCapture::SendAlgoImage(Mat _t1, e_CameraType _t2, int _t3, bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CImageCapture::SendImageToAlgo(Mat _t1, e_CameraType _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CImageCapture::SendImageIndex(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
