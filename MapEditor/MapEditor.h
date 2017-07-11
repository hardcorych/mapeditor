#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MapEditor.h"

#include <mutex>
#include <thread>

#include <qradiobutton.h>
#include <qundostack.h>
#include <qundoview.h>

#include <Block.h>
#include <KeyboardMouseHandler.h>
#include <Map.h>
#include <TableTexPathsWidget.h>

class AddEvent;
class KeyboardMouseHandler;
class ReplaceEvent;
class RemoveEvent;

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
  ~MapEditor();

public:
  unsigned int AddBlockType(BlockType blockType);
  void RemoveBlockType(int id);

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
  void addBlock(AddEvent& addEvent);
  void removeBlock(RemoveEvent& removeEvent);
  void replaceBlock(ReplaceEvent& replaceEvent);
  //block editor
  void changeBlockType(BlockType& blockType, BlockType blockTypeOld);
  void createBlockType(BlockType blockType);
  void deleteBlockType(BlockType blockType);

  //operations with buttons
  void addBlockTypeButton(const BlockType& blockType);
  void deleteBlockTypeButton(int id);
  void setBlockTypeButton(BlockType& blockType);

  void createEmptyMap(int sizeX, int sizeZ);

  void createUndoView();
  void createUndoRedoActions();

  bool event(QEvent* pEvent) override;

private:
  Ui::MapEditorClass ui;

  std::thread _renderThread;

  osg::ref_ptr<KeyboardMouseHandler> _keyboardMouseHandler;

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