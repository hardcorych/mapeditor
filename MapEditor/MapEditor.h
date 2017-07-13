#pragma once

#include <QtWidgets/QMainWindow>

#include <thread>
#include <osg/ref_ptr>

#include <BlockType.h>
#include <ui_MapEditor.h>

class QUndoStack;
class QUndoView;

class AddEvent;
class BlockType;
class KeyboardMouseHandler;
class Map;
class RemoveEvent;
class ReplaceEvent;

class MapEditor : public QMainWindow
{
  Q_OBJECT

public:
  enum CustomEvent
  {
    ADD = QEvent::User + 1,
    REPLACE = QEvent::User + 2,
    REMOVE = QEvent::User + 3,
    UNDO = QEvent::User + 4,
    REDO = QEvent::User + 5,
    CREATE_BLOCKTYPE = QEvent::User + 6,
    CHANGE_BLOCKTYPE = QEvent::User + 7,
    DELETE_BLOCKTYPE = QEvent::User + 8
  };

  typedef std::map<int, BlockType> BlockTypes;

public:
  MapEditor(QWidget *parent = nullptr);
  MapEditor(const MapEditor&) = delete;
  ~MapEditor();

  MapEditor& operator=(const MapEditor&) = delete;

public:
  //returns id of added blocktype
  unsigned int AddBlockType(const BlockType& blockType);

  void DeleteBlockType(int id);

  inline BlockType GetSelectedBlockType();

signals:
  void QuitViewer();
  void QuitAppToMain();

private:
  //render thread
  void renderScene();

  //open dialogs
  void openNewMapDialog();
  void openMapSizeDialog();
  void openBlockEditorDialog();

  //operations with files
  void loadXMLFile();
  void saveXMLFile();
  void saveAsXMLFile();

  //undo/redo commands
  //map editor
  void addBlockCommand(AddEvent& addEvent);
  void removeBlockCommand(RemoveEvent& removeEvent);
  void replaceBlockCommand(ReplaceEvent& replaceEvent);
  //block editor
  void changeBlockTypeCommand(const BlockType& blockType, 
                              BlockType& blockTypeNew);
  void createBlockTypeCommand(BlockType& blockType);
  void deleteBlockTypeCommand(BlockType& blockType);

  //operations with buttons
  void addBlockTypeButton(const BlockType& blockType);
  void deleteBlockTypeButton(int id);
  void setBlockTypeButton(BlockType& blockType);

  void createEmptyMap(int sizeX, int sizeZ);

  void createUndoView();
  void createUndoRedoActions();

  bool event(QEvent* pEvent) override;

  //returns -1 if not found
  int findBlockTypeId(BlockType& blockType);
  bool isBlockTypeExist(BlockType& blockType);

private:
  Ui::MapEditorClass ui;

  std::thread _renderThread;

  QMenu* _fileMenu;
  QMenu* _editMenu;
  QMenu* _settingsMenu;

  QAction* _newAct;
  QAction* _loadAct;
  QAction* _saveAsAct;
  QAction* _saveAct;

  QAction* _resizeMapAct;
  QAction* _blockEditAct;

  QAction* _undoAct;
  QAction* _redoAct;

  QUndoStack* _undoStack;

  QUndoView* _undoView;

  osg::ref_ptr<Map> _map;

  QString _filename;

  int _minMapSize;
  int _maxMapSize;
  int _row;
  int _col;
  int _maxColumnElements;
  int _maxRowElements;

  int _blockSize;

  unsigned int _countIdBlockTypes;

  QButtonGroup* _btnGroupBlocks;
  std::map<std::string, std::string> _texPaths;
  BlockTypes _blockTypes;
};

inline BlockType MapEditor::GetSelectedBlockType()
{
  return _blockTypes[_btnGroupBlocks->checkedId()];
}