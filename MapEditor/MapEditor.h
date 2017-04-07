#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MapEditor.h"
#include <thread>

class MapEditor : public QMainWindow
{
    Q_OBJECT

public:
    MapEditor(QWidget *parent = Q_NULLPTR);
	~MapEditor();

private:
    Ui::MapEditorClass ui;
	std::thread _renderThread;

	void renderScene();

signals:
	void QuitViewer();
	void QuitAppToMain();
};
