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
    QByteArrayData data[48];
    char stringdata0[541];
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
QT_MOC_LITERAL(4, 36, 6), // "NewMap"
QT_MOC_LITERAL(5, 43, 13), // "changeMapSize"
QT_MOC_LITERAL(6, 57, 9), // "blockEdit"
QT_MOC_LITERAL(7, 67, 11), // "LoadXMLFile"
QT_MOC_LITERAL(8, 79, 11), // "SaveXMLFile"
QT_MOC_LITERAL(9, 91, 13), // "SaveAsXMLFile"
QT_MOC_LITERAL(10, 105, 8), // "AddBlock"
QT_MOC_LITERAL(11, 114, 17), // "osg::ref_ptr<Map>"
QT_MOC_LITERAL(12, 132, 3), // "map"
QT_MOC_LITERAL(13, 136, 1), // "x"
QT_MOC_LITERAL(14, 138, 1), // "z"
QT_MOC_LITERAL(15, 140, 9), // "BlockType"
QT_MOC_LITERAL(16, 150, 9), // "blockType"
QT_MOC_LITERAL(17, 160, 11), // "RemoveBlock"
QT_MOC_LITERAL(18, 172, 12), // "ReplaceBlock"
QT_MOC_LITERAL(19, 185, 19), // "osg::ref_ptr<Block>"
QT_MOC_LITERAL(20, 205, 5), // "block"
QT_MOC_LITERAL(21, 211, 15), // "ChangeBlockType"
QT_MOC_LITERAL(22, 227, 16), // "QAbstractButton*"
QT_MOC_LITERAL(23, 244, 7), // "rButton"
QT_MOC_LITERAL(24, 252, 10), // "BlockType&"
QT_MOC_LITERAL(25, 263, 12), // "blockTypeOld"
QT_MOC_LITERAL(26, 276, 15), // "CreateBlockType"
QT_MOC_LITERAL(27, 292, 13), // "QButtonGroup*"
QT_MOC_LITERAL(28, 306, 8), // "btnGroup"
QT_MOC_LITERAL(29, 315, 15), // "DeleteBlockType"
QT_MOC_LITERAL(30, 331, 6), // "button"
QT_MOC_LITERAL(31, 338, 12), // "AddBlockType"
QT_MOC_LITERAL(32, 351, 2), // "id"
QT_MOC_LITERAL(33, 354, 18), // "AddBlockTypeButton"
QT_MOC_LITERAL(34, 373, 13), // "QRadioButton*"
QT_MOC_LITERAL(35, 387, 4), // "int&"
QT_MOC_LITERAL(36, 392, 3), // "row"
QT_MOC_LITERAL(37, 396, 3), // "col"
QT_MOC_LITERAL(38, 400, 15), // "RemoveBlockType"
QT_MOC_LITERAL(39, 416, 21), // "RemoveBlockTypeButton"
QT_MOC_LITERAL(40, 438, 15), // "GetButtonRowCol"
QT_MOC_LITERAL(41, 454, 13), // "GetNextRowCol"
QT_MOC_LITERAL(42, 468, 18), // "std::pair<int,int>"
QT_MOC_LITERAL(43, 487, 13), // "SetPrevRowCol"
QT_MOC_LITERAL(44, 501, 8), // "GetMutex"
QT_MOC_LITERAL(45, 510, 4), // "Undo"
QT_MOC_LITERAL(46, 515, 4), // "Redo"
QT_MOC_LITERAL(47, 520, 20) // "GetSelectedBlockType"

    },
    "MapEditor\0QuitViewer\0\0QuitAppToMain\0"
    "NewMap\0changeMapSize\0blockEdit\0"
    "LoadXMLFile\0SaveXMLFile\0SaveAsXMLFile\0"
    "AddBlock\0osg::ref_ptr<Map>\0map\0x\0z\0"
    "BlockType\0blockType\0RemoveBlock\0"
    "ReplaceBlock\0osg::ref_ptr<Block>\0block\0"
    "ChangeBlockType\0QAbstractButton*\0"
    "rButton\0BlockType&\0blockTypeOld\0"
    "CreateBlockType\0QButtonGroup*\0btnGroup\0"
    "DeleteBlockType\0button\0AddBlockType\0"
    "id\0AddBlockTypeButton\0QRadioButton*\0"
    "int&\0row\0col\0RemoveBlockType\0"
    "RemoveBlockTypeButton\0GetButtonRowCol\0"
    "GetNextRowCol\0std::pair<int,int>\0"
    "SetPrevRowCol\0GetMutex\0Undo\0Redo\0"
    "GetSelectedBlockType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  139,    2, 0x06 /* Public */,
       3,    0,  140,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  141,    2, 0x0a /* Public */,
       5,    0,  142,    2, 0x0a /* Public */,
       6,    0,  143,    2, 0x0a /* Public */,
       7,    0,  144,    2, 0x0a /* Public */,
       8,    0,  145,    2, 0x0a /* Public */,
       9,    0,  146,    2, 0x0a /* Public */,
      10,    4,  147,    2, 0x0a /* Public */,
      17,    4,  156,    2, 0x0a /* Public */,
      18,    3,  165,    2, 0x0a /* Public */,
      21,    3,  172,    2, 0x0a /* Public */,
      26,    2,  179,    2, 0x0a /* Public */,
      29,    2,  184,    2, 0x0a /* Public */,
      31,    2,  189,    2, 0x0a /* Public */,
      33,    3,  194,    2, 0x0a /* Public */,
      38,    1,  201,    2, 0x0a /* Public */,
      39,    1,  204,    2, 0x0a /* Public */,
      40,    3,  207,    2, 0x0a /* Public */,
      41,    0,  214,    2, 0x0a /* Public */,
      43,    0,  215,    2, 0x0a /* Public */,
      44,    0,  216,    2, 0x0a /* Public */,
      45,    0,  217,    2, 0x0a /* Public */,
      46,    0,  218,    2, 0x0a /* Public */,
      47,    0,  219,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, QMetaType::Int, 0x80000000 | 15,   12,   13,   14,   16,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, QMetaType::Int, 0x80000000 | 15,   12,   13,   14,   16,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 19, 0x80000000 | 15,   12,   20,   16,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 24, 0x80000000 | 15,   23,   16,   25,
    QMetaType::Void, 0x80000000 | 27, 0x80000000 | 15,   28,   16,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 15,   30,   16,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 15,   32,   16,
    QMetaType::Void, 0x80000000 | 34, 0x80000000 | 35, 0x80000000 | 35,   23,   36,   37,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, 0x80000000 | 34,   23,
    QMetaType::Void, 0x80000000 | 34, 0x80000000 | 35, 0x80000000 | 35,   23,   36,   37,
    0x80000000 | 42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 15,

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
        case 2: _t->NewMap(); break;
        case 3: _t->changeMapSize(); break;
        case 4: _t->blockEdit(); break;
        case 5: _t->LoadXMLFile(); break;
        case 6: _t->SaveXMLFile(); break;
        case 7: _t->SaveAsXMLFile(); break;
        case 8: _t->AddBlock((*reinterpret_cast< osg::ref_ptr<Map>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< BlockType(*)>(_a[4]))); break;
        case 9: _t->RemoveBlock((*reinterpret_cast< osg::ref_ptr<Map>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< BlockType(*)>(_a[4]))); break;
        case 10: _t->ReplaceBlock((*reinterpret_cast< osg::ref_ptr<Map>(*)>(_a[1])),(*reinterpret_cast< osg::ref_ptr<Block>(*)>(_a[2])),(*reinterpret_cast< BlockType(*)>(_a[3]))); break;
        case 11: _t->ChangeBlockType((*reinterpret_cast< QAbstractButton*(*)>(_a[1])),(*reinterpret_cast< BlockType(*)>(_a[2])),(*reinterpret_cast< BlockType(*)>(_a[3]))); break;
        case 12: _t->CreateBlockType((*reinterpret_cast< QButtonGroup*(*)>(_a[1])),(*reinterpret_cast< BlockType(*)>(_a[2]))); break;
        case 13: _t->DeleteBlockType((*reinterpret_cast< QAbstractButton*(*)>(_a[1])),(*reinterpret_cast< BlockType(*)>(_a[2]))); break;
        case 14: _t->AddBlockType((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< BlockType(*)>(_a[2]))); break;
        case 15: _t->AddBlockTypeButton((*reinterpret_cast< QRadioButton*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 16: _t->RemoveBlockType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->RemoveBlockTypeButton((*reinterpret_cast< QRadioButton*(*)>(_a[1]))); break;
        case 18: _t->GetButtonRowCol((*reinterpret_cast< QRadioButton*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 19: { std::pair<int,int> _r = _t->GetNextRowCol();
            if (_a[0]) *reinterpret_cast< std::pair<int,int>*>(_a[0]) = _r; }  break;
        case 20: _t->SetPrevRowCol(); break;
        case 21: _t->GetMutex(); break;
        case 22: _t->Undo(); break;
        case 23: _t->Redo(); break;
        case 24: { BlockType _r = _t->GetSelectedBlockType();
            if (_a[0]) *reinterpret_cast< BlockType*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QButtonGroup* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QRadioButton* >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QRadioButton* >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QRadioButton* >(); break;
            }
            break;
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
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
