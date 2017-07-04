#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MapEditor.h"

#include <mutex>
#include <thread>

#include <qradiobutton.h>
#include <qundostack.h>
#include <qundoview.h>

#include <Block.h>
#include <TableTexPathsWidget.h>
#include <Map.h>

class MapEditor : public QMainWindow
{
  Q_OBJECT

public:
  MapEditor(QWidget *parent = Q_NULLPTR);
  ~MapEditor();

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

  //ListTexPathsWidget _listTexPathWidget;
  TableTexPathsWidget* _tableTexPathsWidget;

  osg::ref_ptr<Map> _map = new Map(10, 10);

  std::mutex _mutex;

  QString _filename;

  int _minMapSize;
  int _maxMapSize;
  int _row = 0;
  int _col = 0;
  int _maxColumnElements = 5;

  int _blockSize = 16;

  QButtonGroup* _btnGroupBlocks;
  std::map<std::string, std::string> _texPaths;
  std::map<int, BlockType> _blockTypes;

  //методы
  void renderScene();
  void createMap(int sizeX, int sizeZ);
  void createUndoView();
  void createUndoRedoActions();

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
  void RemoveBlock(osg::ref_ptr<Map> map, int x, int z, BlockType blockType);
  void ReplaceBlock(osg::ref_ptr<Map> map, osg::ref_ptr<Block> block, BlockType blockType);
  //block editor
  void ChangeBlockType(QAbstractButton* rButton,
    BlockType& blockType, BlockType blockTypeOld);
  void CreateBlockType(QButtonGroup* btnGroup,
    BlockType blockType);
  void DeleteBlockType(QAbstractButton* button, BlockType blockType);


  void AddBlockType(int id, BlockType blockType);
  void AddBlockTypeButton(QRadioButton* rButton, int& row, int& col);
  void RemoveBlockType(int id);
  void RemoveBlockTypeButton(QRadioButton* rButton);

  //button coords on grid
  void GetButtonRowCol(QRadioButton* rButton, int& row, int& col);

  std::pair<int, int> GetNextRowCol();
  void SetPrevRowCol(); 

  std::mutex& GetMutex()	{ return _mutex; }

  void Undo() { if (_undoStack->canUndo()) _undoStack->undo(); }
  void Redo() { if (_undoStack->canRedo()) _undoStack->redo(); }

  BlockType GetSelectedBlockType()
  { return _blockTypes[_btnGroupBlocks->checkedId()]; }

signals:
  void QuitViewer();
  void QuitAppToMain();
};
