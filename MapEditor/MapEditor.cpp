#include "MapEditor.h"
#include <Viewer.h>
#include <memory>
#include <Map.h>
#include <MouseHandler.h>
#include <osgViewer/ViewerEventHandlers>
#include <qfiledialog.h>
#include <qxmlstream.h>

MapEditor::MapEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	menu = new QMenu(this);

	menu->setTitle("&File");

	newAct = new QAction(tr("&New"), this);
	loadAct = new QAction(tr("&Load"), this);
	saveAct = new QAction(tr("&Save"), this);

	connect(newAct, &QAction::triggered, this, &MapEditor::NewMap);
	connect(loadAct, &QAction::triggered, this, &MapEditor::LoadXMLFile);
	connect(saveAct, &QAction::triggered, this, &MapEditor::SaveXMLFile);

	menu->addAction(newAct);
	menu->addAction(loadAct);
	menu->addAction(saveAct);

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

void MapEditor::NewMap()
{

}

void MapEditor::LoadXMLFile()
{

}

void MapEditor::SaveXMLFile()
{
	//диалог выбора для сохранения файла
	QString filename = QFileDialog::getSaveFileName(
		this, tr("Save XML"), ".",
		tr("XML files (*.xml)"));

	if (filename != "")
	{
		//сохранение файла по заданному пути
		QFile file(filename);
		file.open(QIODevice::WriteOnly);

		//XML поток записи
		QXmlStreamWriter xmlWriter(&file);
		xmlWriter.setAutoFormatting(true);

		xmlWriter.writeStartDocument();		//начало записи в файл

		//сделать запись карты в XML-файл

		xmlWriter.writeEndDocument();		//конец записи в файл
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
	viewer.addEventHandler(new osgViewer::StatsHandler);

	connect(this, &MapEditor::SendBlock, mouseHandler, &MouseHandler::ReceiveBlock, Qt::DirectConnection);
	ui.radioBtnBushes->setChecked(true);
	ui.radioBtnBushes->clicked();

	//установка объектов на сцену
	osg::ref_ptr<Map> map = new Map(10,10);

	viewer.setSceneData(map);
	
	/////////////////////////////
	viewer.run();

	emit QuitAppToMain();
}