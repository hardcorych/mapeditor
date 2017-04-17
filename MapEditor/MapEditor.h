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

	void renderScene();

signals:
	void QuitViewer();
	void QuitAppToMain();
	void SendBlock(TexType texType, FillType fillType);
};
