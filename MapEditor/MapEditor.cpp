#include "MapEditor.h"
#include <Viewer.h>
#include <memory>
#include <MouseHandler.h>
#include <osgViewer/ViewerEventHandlers>
#include <qfiledialog.h>
#include <qxmlstream.h>
#include <qmessagebox.h>
#include <osgGA/TrackballManipulator>
#include <qdebug.h>

MapEditor::MapEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_fileMenu = new QMenu(this);
	_editMenu = new QMenu(this);

	_fileMenu->setTitle("&File");
	_editMenu->setTitle("&Edit");

	_newAct = new QAction(tr("&New"), this);
	_loadAct = new QAction(tr("&Load"), this);
	_saveAct = new QAction(tr("&Save"), this);
	_undoAct = new QAction(tr("&Undo"), this);
	_redoAct = new QAction(tr("&Redo"), this);

	connect(_newAct, &QAction::triggered, this, &MapEditor::NewMap);
	connect(_loadAct, &QAction::triggered, this, &MapEditor::LoadXMLFile);
	connect(_saveAct, &QAction::triggered, this, &MapEditor::SaveXMLFile);

	_fileMenu->addAction(_newAct);
	_fileMenu->addAction(_loadAct);
	_fileMenu->addAction(_saveAct);

	_editMenu->addAction(_undoAct);
	_editMenu->addAction(_redoAct);

	ui.menuBar->addMenu(_fileMenu);
	ui.menuBar->addMenu(_editMenu);

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
	//создание новой карты через модальный диалог
	NewMapDialog newMapDialog(this);

	if (newMapDialog.exec() == QDialog::Accepted)
	{
		_mapSizeX = newMapDialog.GetSizeX();
		_mapSizeZ = newMapDialog.GetSizeZ();
		createMap(_mapSizeX, _mapSizeZ);
	}
}

void MapEditor::createMap(int sizeX, int sizeZ)
{
	std::lock_guard <std::mutex> lgMutex(_mutex);	//для избежания конфликта с перерисовкой
	_map->Remove();
	_map->Set(sizeX, sizeZ);
}

void MapEditor::LoadXMLFile()
{
	//диалог выбора для открытия файла
	QString filename = QFileDialog::getOpenFileName(
		this, tr("Open XML"), ".",
		tr("XML files (*.xml)"));

	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		//обработка ошибки
		QMessageBox::warning(this, "file error",
			"file can't be opened", QMessageBox::Ok);
	}
	else
	{
		//чтение файла
		QXmlStreamReader xmlReader(&file);

		while (!xmlReader.atEnd())
		{
			if (xmlReader.readNextStartElement())
			{
				QString element = xmlReader.name().toString();
				if (element == "sizeX")
				{
					_mapSizeX = xmlReader.readElementText().toInt()/16;	//получаем размер в блоках
				}
				else if (element == "sizeZ")
				{
					_mapSizeZ = xmlReader.readElementText().toInt()/16;	//получаем размер в блоках
					createMap(_mapSizeX, _mapSizeZ);
				}
				else if (element == "block")
				{
					//чтение блока
					//чтение типа блока
					int x, z;
					TexType texType;
					FillType fillType;
					for each (const QXmlStreamAttribute &attr in xmlReader.attributes())
					{
						QString attrStr = attr.name().toString();
						if (attrStr == "texType")
						{
							QString attrValue = attr.value().toString();
							if (attrValue == "BORDER") texType = TexType::BORDER;
							else if (attrValue == "BRICK") texType = TexType::BRICK;
							else if (attrValue == "ARMOR") texType = TexType::ARMOR;
							else if (attrValue == "BUSHES") texType = TexType::BUSHES;
							else if (attrValue == "ICE") texType = TexType::ICE;
							else if (attrValue == "WATER") texType = TexType::WATER;
						}
						else if (attrStr == "fillType")
						{
							QString attrValue = attr.value().toString();
							if (attrValue == "BOTTOM") fillType = FillType::BOTTOM;
							else if (attrValue == "FULL") fillType = FillType::FULL;
							else if (attrValue == "LEFT") fillType = FillType::LEFT;
							else if (attrValue == "RIGHT") fillType = FillType::RIGHT;
							else if (attrValue == "TOP") fillType = FillType::TOP;
						}
					}
					//чтение координат
					xmlReader.readNextStartElement();
					x = xmlReader.readElementText().toInt()-16;		//-16 для согласования
					xmlReader.readNextStartElement();
					z = xmlReader.readElementText().toInt()-16;		//-16 для согласования

					{
						std::lock_guard<std::mutex> lgMutex(_mutex);
						_map->AddBlock(new Block(x, z, texType, fillType), x, z);
					}
				}
			}
		}
		file.close();
	}
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

		//запись карты в XML-файл
		//ок
		xmlWriter.writeStartElement("map");

		xmlWriter.writeTextElement("sizeX", _map->GetSizeX_str());
		xmlWriter.writeTextElement("sizeZ", _map->GetSizeZ_str());

		Block* block = nullptr;
		Tile* tile = nullptr;
		std::pair<QString, QString> bTexFill;	//тип текстуры и заполнения блока

		for (int blockIndex = 0; blockIndex < _map->getNumChildren(); blockIndex++)
		{
			block = dynamic_cast<Block*>(_map->getChild(blockIndex));
			bTexFill = block->GetType_str();

			if (std::get<0>(bTexFill) != "EMPTY")	//пустые блоки не пишутся в файл
			{
				xmlWriter.writeStartElement("block");

				xmlWriter.writeAttribute("texType", std::get<0>(bTexFill));
				xmlWriter.writeAttribute("fillType", std::get<1>(bTexFill));
				xmlWriter.writeTextElement("x", block->GetX_str());
				xmlWriter.writeTextElement("z", block->GetZ_str());
				
				for (int tileIndex = 0; tileIndex < block->getNumChildren(); tileIndex++)
				{
					tile = dynamic_cast<Tile*>(block->getChild(tileIndex));

					if (tile->GetType_str() != "EMPTY")
					{
						xmlWriter.writeStartElement("tile");

						xmlWriter.writeAttribute("type", tile->GetType_str());
						xmlWriter.writeTextElement("x", tile->GetX_str());
						xmlWriter.writeTextElement("z", tile->GetZ_str());

						xmlWriter.writeEndElement();
					}
				}

				xmlWriter.writeEndElement();
			}
		}

		xmlWriter.writeEndElement();

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

	viewer.realize();
	osg::ref_ptr<MouseHandler> mouseHandler = new MouseHandler;
	viewer.addEventHandler(mouseHandler);
	viewer.addEventHandler(new osgViewer::StatsHandler);

	connect(this, &MapEditor::SendBlock, mouseHandler, &MouseHandler::ReceiveBlock, Qt::DirectConnection);
	ui.radioBtnBushes->setChecked(true);
	ui.radioBtnBushes->clicked();

	//установка объектов на сцену
	//osg::ref_ptr<Map> map = new Map(10,10);

	viewer.setSceneData(_map);
	viewer.setCameraManipulator(new osgGA::TrackballManipulator);
	
	//viewer.getCamera()->setClearColor(osg::Vec4(0., 0., 0., 0.));
	
	viewer.realize();
	/////////////////////////////
	//viewer.run();

	while (!viewer.done())
	{
		std::lock_guard<std::mutex> lgMutex(_mutex);	//для избежания конфликта при создании новой карты
		viewer.frame();
	}
	
	emit QuitAppToMain();
}