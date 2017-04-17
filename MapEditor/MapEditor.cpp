#include "MapEditor.h"
#include <Viewer.h>
#include <memory>
#include <Map.h>
#include <MouseHandler.h>

MapEditor::MapEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	menu = new QMenu(this);

	menu->setTitle("&File");

	menu->addAction("&New");
	menu->addAction("&Load");
	menu->addAction("&Save");

	ui.menuBar->addMenu(menu);

	connect(ui.radioBtnBushes, &QRadioButton::clicked, this, &MapEditor::onClickedBushes);
	connect(ui.radioBtnWater, &QRadioButton::clicked, this, &MapEditor::onClickedWater);
	connect(ui.radioBtnIce, &QRadioButton::clicked, this, &MapEditor::onClickedIce);

	connect(ui.radioBtnArmorFull, &QRadioButton::clicked, this, &MapEditor::onClickedArmorFull);
	connect(ui.radioBtnArmorLeft, &QRadioButton::clicked, this, &MapEditor::onClickedArmorLeft);
	connect(ui.radioBtnArmorRight, &QRadioButton::clicked, this, &MapEditor::onClickedArmorRight);
	connect(ui.radioBtnArmorBottom, &QRadioButton::clicked, this, &MapEditor::onClickedArmorBottom);
	connect(ui.radioBtnArmorTop, &QRadioButton::clicked, this, &MapEditor::onClickedArmorTop);

	connect(ui.radioBtnBrickFull, &QRadioButton::clicked, this, &MapEditor::onClickedBrickFull);
	connect(ui.radioBtnBrickLeft, &QRadioButton::clicked, this, &MapEditor::onClickedBrickLeft);
	connect(ui.radioBtnBrickRight, &QRadioButton::clicked, this, &MapEditor::onClickedBrickRight);
	connect(ui.radioBtnBrickBottom, &QRadioButton::clicked, this, &MapEditor::onClickedBrickBottom);
	connect(ui.radioBtnBrickTop, &QRadioButton::clicked, this, &MapEditor::onClickedBrickTop);

	ui.radioBtnBushes->setChecked(true);

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

void MapEditor::onClickedBushes()
{
	emit SendBlock(TexType::BUSHES, FillType::FULL);
}

void MapEditor::onClickedWater()
{
	emit SendBlock(TexType::WATER, FillType::FULL);
}

void MapEditor::onClickedIce()
{
	emit SendBlock(TexType::ICE, FillType::FULL);
}

void MapEditor::onClickedArmorFull()
{
	emit SendBlock(TexType::ARMOR, FillType::FULL);
}

void MapEditor::onClickedArmorLeft()
{
	emit SendBlock(TexType::ARMOR, FillType::LEFT);
}

void MapEditor::onClickedArmorRight()
{
	emit SendBlock(TexType::ARMOR, FillType::RIGHT);
}

void MapEditor::onClickedArmorBottom()
{
	emit SendBlock(TexType::ARMOR, FillType::BOTTOM);
}

void MapEditor::onClickedArmorTop()
{
	emit SendBlock(TexType::ARMOR, FillType::TOP);
}

void MapEditor::onClickedBrickFull()
{
	emit SendBlock(TexType::BRICK, FillType::FULL);
}

void MapEditor::onClickedBrickLeft()
{
	emit SendBlock(TexType::BRICK, FillType::LEFT);
}

void MapEditor::onClickedBrickRight()
{
	emit SendBlock(TexType::BRICK, FillType::RIGHT);
}

void MapEditor::onClickedBrickBottom()
{
	emit SendBlock(TexType::BRICK, FillType::BOTTOM);
}

void MapEditor::onClickedBrickTop()
{
	emit SendBlock(TexType::BRICK, FillType::TOP);
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

	osg::ref_ptr<MouseHandler> mouseHandler = new MouseHandler;
	viewer.addEventHandler(mouseHandler);

	connect(this, &MapEditor::SendBlock, mouseHandler, &MouseHandler::ReceiveBlock, Qt::DirectConnection);

	//установка объектов на сцену
	osg::ref_ptr<Map> map = new Map;

	viewer.setSceneData(map);

	/////////////////////////////
	viewer.run();

	emit QuitAppToMain();
}