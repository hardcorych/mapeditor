#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MapEditor.h"
#include <thread>
#include <Block.h>

class MapEditor : public QMainWindow
{
    Q_OBJECT

public:
    MapEditor(QWidget *parent = Q_NULLPTR);
	~MapEditor();

private:
    Ui::MapEditorClass ui;
	std::thread _renderThread;
	QMenu* menu;
	QAction* newAct;
	QAction* loadAct;
	QAction* saveAct;

	void renderScene();

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

	//операции с файлами
	void NewMap();
	void LoadXMLFile();
	void SaveXMLFile();

signals:
	void QuitViewer();
	void QuitAppToMain();
	void SendBlock(TexType texType, FillType fillType);
};
