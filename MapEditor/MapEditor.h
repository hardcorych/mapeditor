#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MapEditor.h"

#include <mutex>
#include <thread>

#include <qradiobutton.h>
#include <qundostack.h>
#include <qundoview.h>

#include <Block.h>
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

  osg::ref_ptr<Map> _map = new Map(10, 10);

  std::mutex _mutex;

  QString _filename;

  int _minMapSize;
  int _maxMapSize;
  int _row = 0;
  int _col = 0;
  int _maxColumnElements = 5;

  int _blockSize = 16;

  //!!!
  QButtonGroup* _btnGroupBlocks;
  std::map<std::string, std::string> _defaultTexPaths;
  std::map<int, BlockType> _blockTypes;

  //методы
  void readTextures();

  void renderScene();
  void createMap(int sizeX, int sizeZ);
  void createUndoView();
  void createUndoRedoActions();
  //bool isFoundCoordsErrors(int coord, QString coordType);		//функция проверки ошибок

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
  void AddBlock(osg::ref_ptr<Block> block, BlockType blockType);
  void RemoveBlock(osg::ref_ptr<Block> block);
  void ReplaceBlock(osg::ref_ptr<Block> block, BlockType blockType);
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

  void GetButtonRowCol(QRadioButton* rButton, int& row, int& col);

  std::pair<int, int> GetNextRowCol();
  void SetPrevRowCol();

  void Undo();    //????

  std::mutex& GetMutex()	{ return _mutex; }

signals:
  void QuitViewer();
  void QuitAppToMain();
  void SendBlockType(BlockType blockType);
};
