#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MapEditor.h"

#include <mutex>
#include <thread>

#include <qundostack.h>
#include <qundoview.h>

#include <Block.h>
#include <BlockEditor.h>
#include <Editor.h>
#include <Map.h>
#include <MapSizeDialog.h>

class MapEditor : public QMainWindow,
  public Editor
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

  //QAction* _undoAct;
  //QAction* _redoAct;

  //QUndoStack* _undoStack;
  QUndoView* _undoView;

  osg::ref_ptr<Map> _map = new Map(10, 10);

  //QString _errorText;
  std::mutex _mutex;

  QString _filename;

  BlockEditor _blockEditor;

  int _minMapSize;
  int _maxMapSize;

  //методы

  void readTextures();

  void renderScene();
  void createMap(int sizeX, int sizeZ);
  void createUndoView();
  void createUndoRedoActions();
  //bool isFoundCoordsErrors(int coord, QString coordType);		//функция проверки ошибок

  public slots:
  //???
  void onClickedBushes();
  void onClickedWater();
  void onClickedIce();

  void onClickedArmorFull();
  void onClickedArmorLeft();
  void onClickedArmorRight();
  void onClickedArmorTop();
  void onClickedArmorBottom();

  void onClickedBrickFull();
  void onClickedBrickLeft();
  void onClickedBrickRight();
  void onClickedBrickTop();
  void onClickedBrickBottom();

  void NewMap();
  void changeMapSize();

  //operations with files
  void LoadXMLFile();
  void SaveXMLFile();
  void SaveAsXMLFile();

  void AddBlock(osg::ref_ptr<Block> block, TexType type, FillType fType);
  void RemoveBlock(osg::ref_ptr<Block> block);
  void ReplaceBlock(osg::ref_ptr<Block> block, TexType type, FillType fType);

  void Undo();    //????

  std::mutex& GetMutex()	{ return _mutex; }

signals:
  void QuitViewer();
  void QuitAppToMain();
  void SendBlock(TexType texType, FillType fillType);
};
