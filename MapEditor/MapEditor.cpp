#include "MapEditor.h"
#include <Viewer.h>
#include <memory>
#include <MouseHandler.h>
#include <osgViewer/ViewerEventHandlers>
#include <qfiledialog.h>
#include <qxmlstream.h>
#include <qmessagebox.h>
#include <mutex>

MapEditor::MapEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_menu = new QMenu(this);

	_menu->setTitle("&File");

	_newAct = new QAction(tr("&New"), this);
	_loadAct = new QAction(tr("&Load"), this);
	_saveAct = new QAction(tr("&Save"), this);

	connect(_newAct, &QAction::triggered, this, &MapEditor::NewMap);
	connect(_loadAct, &QAction::triggered, this, &MapEditor::LoadXMLFile);
	connect(_saveAct, &QAction::triggered, this, &MapEditor::SaveXMLFile);

	_menu->addAction(_newAct);
	_menu->addAction(_loadAct);
	_menu->addAction(_saveAct);

	ui.menuBar->addMenu(_menu);

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
	std::mutex mutex;
	{
		std::lock_guard <std::mutex> lgMutex(mutex);
		_map->Remove();
		//можно выполнить, если размер отличен от предыдущего
		//иногда вылазит ошибка с traverse
		_map->Set(7, 7);
	}
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
					_mapSizeX = xmlReader.readElementText().toInt();
				}
				else if (element == "sizeZ")
				{
					_mapSizeZ = xmlReader.readElementText().toInt();
				}
			}
		}
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

	osg::ref_ptr<MouseHandler> mouseHandler = new MouseHandler;
	viewer.addEventHandler(mouseHandler);
	viewer.addEventHandler(new osgViewer::StatsHandler);

	connect(this, &MapEditor::SendBlock, mouseHandler, &MouseHandler::ReceiveBlock, Qt::DirectConnection);
	ui.radioBtnBushes->setChecked(true);
	ui.radioBtnBushes->clicked();

	//установка объектов на сцену
	//osg::ref_ptr<Map> map = new Map(10,10);

	viewer.setSceneData(_map);

	/////////////////////////////
	viewer.run();

	emit QuitAppToMain();
}