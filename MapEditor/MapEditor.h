#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MapEditor.h"
#include <thread>
#include <Block.h>
#include <Map.h>
#include <mutex>
#include <NewMapDialog.h>
#include <qundostack.h>
#include <qundoview.h>

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
	QAction* _newAct;
	QAction* _loadAct;
	QAction* _saveAct;
	QAction* _undoAct;
	QAction* _redoAct;

	QUndoStack* _undoStack;
	QUndoView* _undoView;

	osg::ref_ptr<Map> _map = new Map(10,10);
	int _mapSizeX;
	int _mapSizeZ;
	std::mutex _mutex;

	void renderScene();
	void createMap(int sizeX, int sizeZ);
	void createUndoView();
	void createUndoRedoActions();

	public slots:
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
	//операции с файлами
	void LoadXMLFile();
	void SaveXMLFile();

	void AddBlock(Block* block, TexType type, FillType fType);
	void RemoveBlock(Block* block);

	void onClickedChangeSize();

	void Undo();

signals:
	void QuitViewer();
	void QuitAppToMain();
	void SendBlock(TexType texType, FillType fillType);
};
