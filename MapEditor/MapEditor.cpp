#include "MapEditor.h"
#include <Viewer.h>
#include <memory>
#include <Map.h>

MapEditor::MapEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_renderThread = std::thread(&MapEditor::renderScene, this);
}

MapEditor::~MapEditor()
{
	if (_renderThread.joinable())
	{
		emit QuitViewer();
		_renderThread.join();
	}
}

void MapEditor::renderScene()
{
	Viewer viewer;

	connect(this, &MapEditor::QuitViewer, &viewer, &Viewer::onQuitViewer, Qt::DirectConnection);

	//настройка окна
	int xViewer = 100;
	int yViewer = 100;
	int wViewer = 640;
	int hViewer = 480;

	viewer.setUpViewInWindow(xViewer, yViewer, wViewer, hViewer);

	//установка объектов на сцену
	osg::ref_ptr<Map> map = new Map;

	osg::ref_ptr<Tile> tile = new Tile;

	//viewer.setSceneData(tile);
	viewer.setSceneData(map);

	/////////////////////////////
	viewer.run();

	emit QuitAppToMain();
}