/****************************************************************************
** Meta object code from reading C++ file 'KeyboardMouseHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KeyboardMouseHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KeyboardMouseHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KeyboardMouseHandler_t {
    QByteArrayData data[15];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KeyboardMouseHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KeyboardMouseHandler_t qt_meta_stringdata_KeyboardMouseHandler = {
    {
QT_MOC_LITERAL(0, 0, 20), // "KeyboardMouseHandler"
QT_MOC_LITERAL(1, 21, 12), // "AddableBlock"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 6), // "Block*"
QT_MOC_LITERAL(4, 42, 5), // "block"
QT_MOC_LITERAL(5, 48, 7), // "TexType"
QT_MOC_LITERAL(6, 56, 4), // "type"
QT_MOC_LITERAL(7, 61, 8), // "FillType"
QT_MOC_LITERAL(8, 70, 5), // "fType"
QT_MOC_LITERAL(9, 76, 14), // "RemovableBlock"
QT_MOC_LITERAL(10, 91, 16), // "ReplaceableBlock"
QT_MOC_LITERAL(11, 108, 4), // "Undo"
QT_MOC_LITERAL(12, 113, 4), // "Redo"
QT_MOC_LITERAL(13, 118, 12), // "ReceiveBlock"
QT_MOC_LITERAL(14, 131, 8) // "fillType"

    },
    "KeyboardMouseHandler\0AddableBlock\0\0"
    "Block*\0block\0TexType\0type\0FillType\0"
    "fType\0RemovableBlock\0ReplaceableBlock\0"
    "Undo\0Redo\0ReceiveBlock\0fillType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KeyboardMouseHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x06 /* Public */,
       9,    1,   51,    2, 0x06 /* Public */,
      10,    3,   54,    2, 0x06 /* Public */,
      11,    0,   61,    2, 0x06 /* Public */,
      12,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    2,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    6,   14,

       0        // eod
};

void KeyboardMouseHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KeyboardMouseHandler *_t = static_cast<KeyboardMouseHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddableBlock((*reinterpret_cast< Block*(*)>(_a[1])),(*reinterpret_cast< TexType(*)>(_a[2])),(*reinterpret_cast< FillType(*)>(_a[3]))); break;
        case 1: _t->RemovableBlock((*reinterpret_cast< Block*(*)>(_a[1]))); break;
        case 2: _t->ReplaceableBlock((*reinterpret_cast< Block*(*)>(_a[1])),(*reinterpret_cast< TexType(*)>(_a[2])),(*reinterpret_cast< FillType(*)>(_a[3]))); break;
        case 3: _t->Undo(); break;
        case 4: _t->Redo(); break;
        case 5: _t->ReceiveBlock((*reinterpret_cast< TexType(*)>(_a[1])),(*reinterpret_cast< FillType(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KeyboardMouseHandler::*_t)(Block * , TexType , FillType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyboardMouseHandler::AddableBlock)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (KeyboardMouseHandler::*_t)(Block * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyboardMouseHandler::RemovableBlock)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (KeyboardMouseHandler::*_t)(Block * , TexType , FillType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyboardMouseHandler::ReplaceableBlock)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (KeyboardMouseHandler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyboardMouseHandler::Undo)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (KeyboardMouseHandler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyboardMouseHandler::Redo)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject KeyboardMouseHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KeyboardMouseHandler.data,
      qt_meta_data_KeyboardMouseHandler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KeyboardMouseHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KeyboardMouseHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KeyboardMouseHandler.stringdata0))
        return static_cast<void*>(const_cast< KeyboardMouseHandler*>(this));
    if (!strcmp(_clname, "osgGA::GUIEventHandler"))
        return static_cast< osgGA::GUIEventHandler*>(const_cast< KeyboardMouseHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int KeyboardMouseHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void KeyboardMouseHandler::AddableBlock(Block * _t1, TexType _t2, FillType _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KeyboardMouseHandler::RemovableBlock(Block * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KeyboardMouseHandler::ReplaceableBlock(Block * _t1, TexType _t2, FillType _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void KeyboardMouseHandler::Undo()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void KeyboardMouseHandler::Redo()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
