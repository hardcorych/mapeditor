/****************************************************************************
** Meta object code from reading C++ file 'MouseHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MouseHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MouseHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MouseHandler_t {
    QByteArrayData data[14];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MouseHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MouseHandler_t qt_meta_stringdata_MouseHandler = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MouseHandler"
QT_MOC_LITERAL(1, 13, 12), // "AddableBlock"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "Block*"
QT_MOC_LITERAL(4, 34, 5), // "block"
QT_MOC_LITERAL(5, 40, 7), // "TexType"
QT_MOC_LITERAL(6, 48, 4), // "type"
QT_MOC_LITERAL(7, 53, 8), // "FillType"
QT_MOC_LITERAL(8, 62, 5), // "fType"
QT_MOC_LITERAL(9, 68, 14), // "RemovableBlock"
QT_MOC_LITERAL(10, 83, 4), // "Undo"
QT_MOC_LITERAL(11, 88, 4), // "Redo"
QT_MOC_LITERAL(12, 93, 12), // "ReceiveBlock"
QT_MOC_LITERAL(13, 106, 8) // "fillType"

    },
    "MouseHandler\0AddableBlock\0\0Block*\0"
    "block\0TexType\0type\0FillType\0fType\0"
    "RemovableBlock\0Undo\0Redo\0ReceiveBlock\0"
    "fillType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MouseHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x06 /* Public */,
       9,    1,   46,    2, 0x06 /* Public */,
      10,    0,   49,    2, 0x06 /* Public */,
      11,    0,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    6,   13,

       0        // eod
};

void MouseHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MouseHandler *_t = static_cast<MouseHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddableBlock((*reinterpret_cast< Block*(*)>(_a[1])),(*reinterpret_cast< TexType(*)>(_a[2])),(*reinterpret_cast< FillType(*)>(_a[3]))); break;
        case 1: _t->RemovableBlock((*reinterpret_cast< Block*(*)>(_a[1]))); break;
        case 2: _t->Undo(); break;
        case 3: _t->Redo(); break;
        case 4: _t->ReceiveBlock((*reinterpret_cast< TexType(*)>(_a[1])),(*reinterpret_cast< FillType(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MouseHandler::*_t)(Block * , TexType , FillType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MouseHandler::AddableBlock)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MouseHandler::*_t)(Block * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MouseHandler::RemovableBlock)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MouseHandler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MouseHandler::Undo)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MouseHandler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MouseHandler::Redo)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject MouseHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MouseHandler.data,
      qt_meta_data_MouseHandler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MouseHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MouseHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MouseHandler.stringdata0))
        return static_cast<void*>(const_cast< MouseHandler*>(this));
    if (!strcmp(_clname, "osgGA::GUIEventHandler"))
        return static_cast< osgGA::GUIEventHandler*>(const_cast< MouseHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int MouseHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void MouseHandler::AddableBlock(Block * _t1, TexType _t2, FillType _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MouseHandler::RemovableBlock(Block * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MouseHandler::Undo()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void MouseHandler::Redo()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
