/****************************************************************************
** Meta object code from reading C++ file 'MapEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MapEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapEditor_t {
    QByteArrayData data[22];
    char stringdata0[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapEditor_t qt_meta_stringdata_MapEditor = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MapEditor"
QT_MOC_LITERAL(1, 10, 10), // "QuitViewer"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "QuitAppToMain"
QT_MOC_LITERAL(4, 36, 13), // "SendBlockType"
QT_MOC_LITERAL(5, 50, 9), // "BlockType"
QT_MOC_LITERAL(6, 60, 9), // "blockType"
QT_MOC_LITERAL(7, 70, 21), // "onClickedCreateButton"
QT_MOC_LITERAL(8, 92, 21), // "onClickedDeleteButton"
QT_MOC_LITERAL(9, 114, 6), // "NewMap"
QT_MOC_LITERAL(10, 121, 13), // "changeMapSize"
QT_MOC_LITERAL(11, 135, 9), // "blockEdit"
QT_MOC_LITERAL(12, 145, 11), // "LoadXMLFile"
QT_MOC_LITERAL(13, 157, 11), // "SaveXMLFile"
QT_MOC_LITERAL(14, 169, 13), // "SaveAsXMLFile"
QT_MOC_LITERAL(15, 183, 8), // "AddBlock"
QT_MOC_LITERAL(16, 192, 19), // "osg::ref_ptr<Block>"
QT_MOC_LITERAL(17, 212, 5), // "block"
QT_MOC_LITERAL(18, 218, 11), // "RemoveBlock"
QT_MOC_LITERAL(19, 230, 12), // "ReplaceBlock"
QT_MOC_LITERAL(20, 243, 4), // "Undo"
QT_MOC_LITERAL(21, 248, 8) // "GetMutex"

    },
    "MapEditor\0QuitViewer\0\0QuitAppToMain\0"
    "SendBlockType\0BlockType\0blockType\0"
    "onClickedCreateButton\0onClickedDeleteButton\0"
    "NewMap\0changeMapSize\0blockEdit\0"
    "LoadXMLFile\0SaveXMLFile\0SaveAsXMLFile\0"
    "AddBlock\0osg::ref_ptr<Block>\0block\0"
    "RemoveBlock\0ReplaceBlock\0Undo\0GetMutex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    1,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   99,    2, 0x0a /* Public */,
       8,    0,  100,    2, 0x0a /* Public */,
       9,    0,  101,    2, 0x0a /* Public */,
      10,    0,  102,    2, 0x0a /* Public */,
      11,    0,  103,    2, 0x0a /* Public */,
      12,    0,  104,    2, 0x0a /* Public */,
      13,    0,  105,    2, 0x0a /* Public */,
      14,    0,  106,    2, 0x0a /* Public */,
      15,    2,  107,    2, 0x0a /* Public */,
      18,    1,  112,    2, 0x0a /* Public */,
      19,    2,  115,    2, 0x0a /* Public */,
      20,    0,  120,    2, 0x0a /* Public */,
      21,    0,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 5,   17,    6,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 5,   17,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MapEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapEditor *_t = static_cast<MapEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->QuitViewer(); break;
        case 1: _t->QuitAppToMain(); break;
        case 2: _t->SendBlockType((*reinterpret_cast< BlockType(*)>(_a[1]))); break;
        case 3: _t->onClickedCreateButton(); break;
        case 4: _t->onClickedDeleteButton(); break;
        case 5: _t->NewMap(); break;
        case 6: _t->changeMapSize(); break;
        case 7: _t->blockEdit(); break;
        case 8: _t->LoadXMLFile(); break;
        case 9: _t->SaveXMLFile(); break;
        case 10: _t->SaveAsXMLFile(); break;
        case 11: _t->AddBlock((*reinterpret_cast< osg::ref_ptr<Block>(*)>(_a[1])),(*reinterpret_cast< BlockType(*)>(_a[2]))); break;
        case 12: _t->RemoveBlock((*reinterpret_cast< osg::ref_ptr<Block>(*)>(_a[1]))); break;
        case 13: _t->ReplaceBlock((*reinterpret_cast< osg::ref_ptr<Block>(*)>(_a[1])),(*reinterpret_cast< BlockType(*)>(_a[2]))); break;
        case 14: _t->Undo(); break;
        case 15: _t->GetMutex(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MapEditor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MapEditor::QuitViewer)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MapEditor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MapEditor::QuitAppToMain)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MapEditor::*_t)(BlockType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MapEditor::SendBlockType)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject MapEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MapEditor.data,
      qt_meta_data_MapEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MapEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MapEditor.stringdata0))
        return static_cast<void*>(const_cast< MapEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MapEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MapEditor::QuitViewer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MapEditor::QuitAppToMain()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MapEditor::SendBlockType(BlockType _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
