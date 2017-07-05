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
#include <Viewer.h>

class KeyboardMouseHandler;

class MapEditor : public QMainWindow
{
  Q_OBJECT

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
  void RemoveBlock(osg::ref_ptr<Map> map, int x, int z, BlockType blockType);
  void ReplaceBlock(osg::ref_ptr<Map> map,
                    osg::ref_ptr<Block> block,
                    BlockType blockType);
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

  void GetNextRowCol(int& rowOutput, int& colOutput);
  void SetPrevRowCol();

  std::mutex& GetMutex()	{ return _mutex; }

  inline void Undo();
  inline void Redo();

  inline BlockType GetSelectedBlockType();

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

  Viewer _viewer;
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

  QButtonGroup* _btnGroupBlocks;
  std::map<std::string, std::string> _texPaths;
  std::map<int, BlockType> _blockTypes;
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
