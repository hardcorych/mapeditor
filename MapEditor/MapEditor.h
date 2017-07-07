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

class KeyboardMouseHandler;

class MapEditor : public QMainWindow
{
  Q_OBJECT

public:
  typedef std::map<int, BlockType> BlockTypes;

public:
  MapEditor(QWidget *parent = Q_NULLPTR);
  ~MapEditor();

public slots:
  void NewMap();
  void changeMapSize();

  void blockEdit();

  //operations with files
  void LoadXMLFile();
  void SaveXMLFile();
  void SaveAsXMLFile();

  //undo/redo commands
  //map editor
  void AddBlock(osg::ref_ptr<Map> map, int x, int z, BlockType blockType);
  void RemoveBlock(osg::ref_ptr<Map>& map, int x, int z, BlockType blockType);
  void ReplaceBlock(osg::ref_ptr<Map> map,
                    osg::ref_ptr<Block> block,
                    BlockType blockType);
  //block editor
  void ChangeBlockType(BlockType& blockType, BlockType blockTypeOld);
  void CreateBlockType(BlockType blockType);
  void DeleteBlockType(BlockType blockType);

  unsigned int AddBlockType(BlockType blockType);
  void AddBlockTypeButton(const BlockType& blockType);
  void RemoveBlockType(int id);
  void RemoveBlockTypeButton(int id);

  void SetBlockTypeButton(BlockType& blockType);

  //button coords on grid
  void GetButtonRowCol(QRadioButton* rButton, int& row, int& col);

  void GetNextRowCol(int& rowOutput, int& colOutput);
  void SetPrevRowCol();

  std::mutex& GetMutex()	{ return _mutex; }

  inline void Undo();
  inline void Redo();

  inline BlockType GetSelectedBlockType();
  inline void SetSelectedBlockType(const BlockType& blockType);

  inline QAbstractButton* GetCheckedButton();

signals:
  void QuitViewer();
  void QuitAppToMain();

private:
  void renderScene();
  void createMap(int sizeX, int sizeZ);
  void createUndoView();
  void createUndoRedoActions();

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

  TableTexPathsWidget* _tableTexPathsWidget;

  osg::ref_ptr<Map> _map;

  std::mutex _mutex;

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

inline void MapEditor::Undo() 
{ 
  if (_undoStack->canUndo()) _undoStack->undo();
}

inline void MapEditor::Redo()
{ 
  if (_undoStack->canRedo()) _undoStack->redo();
}

inline BlockType MapEditor::GetSelectedBlockType()
{
  return _blockTypes[_btnGroupBlocks->checkedId()];
}

inline QAbstractButton* MapEditor::GetCheckedButton()
{
  return _btnGroupBlocks->checkedButton();
}

inline void MapEditor::SetSelectedBlockType(const BlockType& blockType)
{
  _blockTypes[_btnGroupBlocks->checkedId()] = blockType;
}