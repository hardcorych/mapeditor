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
    QByteArrayData data[16];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KeyboardMouseHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KeyboardMouseHandler_t qt_meta_stringdata_KeyboardMouseHandler = {
    {
QT_MOC_LITERAL(0, 0, 20), // "KeyboardMouseHandler"
QT_MOC_LITERAL(1, 21, 11), // "RemoveBlock"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "osg::ref_ptr<Map>"
QT_MOC_LITERAL(4, 52, 3), // "map"
QT_MOC_LITERAL(5, 56, 1), // "x"
QT_MOC_LITERAL(6, 58, 1), // "z"
QT_MOC_LITERAL(7, 60, 9), // "BlockType"
QT_MOC_LITERAL(8, 70, 9), // "blockType"
QT_MOC_LITERAL(9, 80, 8), // "AddBlock"
QT_MOC_LITERAL(10, 89, 16), // "ReplaceableBlock"
QT_MOC_LITERAL(11, 106, 19), // "osg::ref_ptr<Block>"
QT_MOC_LITERAL(12, 126, 5), // "block"
QT_MOC_LITERAL(13, 132, 4), // "Undo"
QT_MOC_LITERAL(14, 137, 4), // "Redo"
QT_MOC_LITERAL(15, 142, 12) // "ReceiveBlock"

    },
    "KeyboardMouseHandler\0RemoveBlock\0\0"
    "osg::ref_ptr<Map>\0map\0x\0z\0BlockType\0"
    "blockType\0AddBlock\0ReplaceableBlock\0"
    "osg::ref_ptr<Block>\0block\0Undo\0Redo\0"
    "ReceiveBlock"
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
       1,    4,   44,    2, 0x06 /* Public */,
       9,    4,   53,    2, 0x06 /* Public */,
      10,    2,   62,    2, 0x06 /* Public */,
      13,    0,   67,    2, 0x06 /* Public */,
      14,    0,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int, 0x80000000 | 7,    4,    5,    6,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int, 0x80000000 | 7,    4,    5,    6,    8,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 7,   12,    8,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void KeyboardMouseHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KeyboardMouseHandler *_t = static_cast<KeyboardMouseHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->RemoveBlock((*reinterpret_cast< osg::ref_ptr<Map>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< BlockType(*)>(_a[4]))); break;
        case 1: _t->AddBlock((*reinterpret_cast< osg::ref_ptr<Map>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< BlockType(*)>(_a[4]))); break;
        case 2: _t->ReplaceableBlock((*reinterpret_cast< osg::ref_ptr<Block>(*)>(_a[1])),(*reinterpret_cast< BlockType(*)>(_a[2]))); break;
        case 3: _t->Undo(); break;
        case 4: _t->Redo(); break;
        case 5: _t->ReceiveBlock((*reinterpret_cast< BlockType(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KeyboardMouseHandler::*_t)(osg::ref_ptr<Map> , int , int , BlockType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyboardMouseHandler::RemoveBlock)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (KeyboardMouseHandler::*_t)(osg::ref_ptr<Map> , int , int , BlockType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyboardMouseHandler::AddBlock)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (KeyboardMouseHandler::*_t)(osg::ref_ptr<Block> , BlockType );
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
void KeyboardMouseHandler::RemoveBlock(osg::ref_ptr<Map> _t1, int _t2, int _t3, BlockType _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KeyboardMouseHandler::AddBlock(osg::ref_ptr<Map> _t1, int _t2, int _t3, BlockType _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KeyboardMouseHandler::ReplaceableBlock(osg::ref_ptr<Block> _t1, BlockType _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
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
