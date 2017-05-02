#include "MapEditor.h"
#include <Viewer.h>
#include <memory>
#include <KeyboardMouseHandler.h>
#include <osgViewer/ViewerEventHandlers>
#include <qfiledialog.h>
#include <qxmlstream.h>
#include <qmessagebox.h>
#include <osgGA/TrackballManipulator>
#include <qdebug.h>
#include <Commands.h>

MapEditor::MapEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.spnBoxSizeX->setMinimum(5);
	ui.spnBoxSizeX->setMaximum(30);

	ui.spnBoxSizeZ->setMinimum(5);
	ui.spnBoxSizeZ->setMaximum(30);

	_fileMenu = new QMenu(this);
	_editMenu = new QMenu(this);

	_fileMenu->setTitle("&File");
	_editMenu->setTitle("&Edit");

	_newAct = new QAction(tr("&New"), this);
	_loadAct = new QAction(tr("&Load"), this);
	_saveAct = new QAction(tr("&Save"), this);

	_undoStack = new QUndoStack(this);

	createUndoRedoActions();
	createUndoView();

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

	connect(ui.pBtnChangeSize, &QPushButton::clicked, this, &MapEditor::onClickedChangeSize);

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
	//�������� ����� ����� ����� ��������� ������
	NewMapDialog newMapDialog(this);

	if (newMapDialog.exec() == QDialog::Accepted)
	{
		_mapSizeX = newMapDialog.GetSizeX();
		_mapSizeZ = newMapDialog.GetSizeZ();
		createMap(_mapSizeX, _mapSizeZ);
		if (!_undoStack->isClean()) _undoStack->clear();
	}
}

void MapEditor::createMap(int sizeX, int sizeZ)
{
	_map->Remove();
	_map->Set(sizeX, sizeZ);
}

void MapEditor::LoadXMLFile()
{
	//������� ��������� ������

	//������ ������ ��� �������� �����
	QString filename = QFileDialog::getOpenFileName(
		this, tr("Open XML"), ".",
		tr("XML files (*.xml)"));

	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		//��������� ������?
		//QMessageBox::warning(this, "file error", "file can't be opened", QMessageBox::Ok);
	}
	else
	{
		if (!_undoStack->isClean()) _undoStack->clear();
		//������ �����
		QXmlStreamReader xmlReader(&file);

		//��� ������ ������
		bool isError = false;
		QString errorText;

		bool isWrongType = false;
		bool isWrongFill = false;

		while (!xmlReader.atEnd())
		{
			if (xmlReader.readNextStartElement())
			{
				QString element = xmlReader.name().toString();
				if (element == "sizeX")
				{
					_mapSizeX = xmlReader.readElementText().toInt();
					if (_mapSizeX < 0)
					{
						isError = true;
						errorText = "������������� ������ ����� �� X";
						break;
					}
					if (_mapSizeX % 16 != 0)
					{
						isError = true;
						errorText = "������������ ������ ����� �� X: �� ������ 16";
						break;
					}
					if (_mapSizeX < ui.spnBoxSizeX->minimum() * 16 ||
						_mapSizeX > ui.spnBoxSizeX->maximum() * 16)
					{
						isError = true;
						errorText = "������ ����� ����� ���� �� " + QString::number(ui.spnBoxSizeX->minimum()) +
							"�� " + QString::number(ui.spnBoxSizeX->maximum()) + " ������";
						break;
					}
					//�������� ������ � ������
					_mapSizeX /= 16;
				}
				else if (element == "sizeZ")
				{
					_mapSizeZ = xmlReader.readElementText().toInt();
					if (_mapSizeZ < 0)
					{
						isError = true;
						errorText = "������������� ������ ����� �� Z";
						break;
					}
					if (_mapSizeZ % 16 != 0)
					{
						isError = true;
						errorText = "������������ ������ ����� �� Z: �� ������ 16";
						break;
					}
					if (_mapSizeZ < ui.spnBoxSizeZ->minimum() * 16 ||
						_mapSizeZ > ui.spnBoxSizeZ->maximum() * 16)
					{
						isError = true;
						errorText = "������ ����� ����� ���� �� " + QString::number(ui.spnBoxSizeZ->minimum()) +
							"�� " + QString::number(ui.spnBoxSizeZ->maximum()) + " ������";
						break;
					}
					//�������� ������ � ������
					_mapSizeZ /= 16;
					createMap(_mapSizeX, _mapSizeZ);
				}
				else if (element == "block")
				{
					//������ �����
					//������ ���� �����
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
					//������ ���������
					xmlReader.readNextStartElement();
					x = xmlReader.readElementText().toInt()-16;		//-16 ��� ������������
					xmlReader.readNextStartElement();
					z = xmlReader.readElementText().toInt()-16;		//-16 ��� ������������

					_map->AddBlock(new Block(x, z, texType, fillType), x, z);
				}
			}
		}
		file.close();
		
		//��������� �� ������
		if (isError)
		{
			QMessageBox::critical(this, "File error", errorText, QMessageBox::Ok);
		}
	}
}

void MapEditor::SaveXMLFile()
{
	//������ ������ ��� ���������� �����
	QString filename = QFileDialog::getSaveFileName(
		this, tr("Save XML"), ".",
		tr("XML files (*.xml)"));

	if (filename != "")
	{
		//���������� ����� �� ��������� ����
		QFile file(filename);
		file.open(QIODevice::WriteOnly);

		//XML ����� ������
		QXmlStreamWriter xmlWriter(&file);
		xmlWriter.setAutoFormatting(true);

		xmlWriter.writeStartDocument();		//������ ������ � ����

		//������ ����� � XML-����
		xmlWriter.writeStartElement("map");

		xmlWriter.writeTextElement("sizeX", _map->GetSizeX_str());
		xmlWriter.writeTextElement("sizeZ", _map->GetSizeZ_str());

		osg::ref_ptr<Block> block = nullptr;
		osg::ref_ptr<Tile> tile = nullptr;
		
		std::pair<QString, QString> bTexFill;	//��� �������� � ���������� �����

		for (int blockIndex = 0; blockIndex < _map->getNumChildren(); blockIndex++)
		{
			block = dynamic_cast<Block*>(_map->getChild(blockIndex));
			bTexFill = block->GetType_str();

			if (std::get<0>(bTexFill) != "EMPTY")	//������ ����� �� ������� � ����
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

		xmlWriter.writeEndDocument();		//����� ������ � ����
		file.close();
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

	//��������� ����
	int xViewer = 100;
	int yViewer = 100;
	int wViewer = 640;
	int hViewer = 480;

	viewer.setUpViewInWindow(xViewer, yViewer, wViewer, hViewer);

	viewer.realize();
	
	osg::ref_ptr<KeyboardMouseHandler> keyboardMouseHandler = new KeyboardMouseHandler;
	viewer.addEventHandler(keyboardMouseHandler);
	viewer.addEventHandler(new osgViewer::StatsHandler);

	connect(this, &MapEditor::SendBlock, keyboardMouseHandler, &KeyboardMouseHandler::ReceiveBlock, Qt::DirectConnection);
	connect(keyboardMouseHandler, &KeyboardMouseHandler::AddableBlock, this, &MapEditor::AddBlock, Qt::DirectConnection);
	connect(keyboardMouseHandler, &KeyboardMouseHandler::RemovableBlock, this, &MapEditor::RemoveBlock, Qt::DirectConnection);
	connect(keyboardMouseHandler, &KeyboardMouseHandler::ReplaceableBlock, this, &MapEditor::ReplaceBlock, Qt::DirectConnection);
	connect(keyboardMouseHandler, &KeyboardMouseHandler::Undo, _undoStack, &QUndoStack::undo);
	connect(keyboardMouseHandler, &KeyboardMouseHandler::Redo, _undoStack, &QUndoStack::redo);

	ui.radioBtnBushes->setChecked(true);
	ui.radioBtnBushes->clicked();

	//��������� �������� �� �����
	//osg::ref_ptr<Map> map = new Map(10,10);

	viewer.setSceneData(_map);
	viewer.setCameraManipulator(new osgGA::TrackballManipulator);
	
	//viewer.getCamera()->setClearColor(osg::Vec4(0., 0., 0., 0.));
	
	viewer.realize();
	/////////////////////////////
	//viewer.run();

	while (!viewer.done())
	{
		//std::lock_guard<std::mutex> lgMutex(_mutex);	//��� ��������� ��������� ��� �������� ����� �����
		std::lock_guard<std::mutex> lgMutex(_map->GetMutex());
		viewer.frame();
	}
	
	emit QuitAppToMain();
}

void MapEditor::createUndoView()
{
	_undoView = new QUndoView(_undoStack);
	_undoView->setWindowTitle(tr("command list"));
	_undoView->show();
	_undoView->setAttribute(Qt::WA_QuitOnClose, false);
}

void MapEditor::createUndoRedoActions()
{
	_undoAct = _undoStack->createUndoAction(this, tr("&Undo"));
	_undoAct->setShortcuts(QKeySequence::Undo);

	_redoAct = _undoStack->createRedoAction(this, tr("&Redo"));
	_redoAct->setShortcuts(QKeySequence::Redo);
}

void MapEditor::AddBlock(osg::ref_ptr<Block> block, TexType type, FillType fType)
{
	QUndoCommand* addCommand = new AddCommand(block, type, fType);
	_undoStack->push(addCommand);
}

void MapEditor::RemoveBlock(osg::ref_ptr<Block> block)
{
	QUndoCommand* removeCommand = new RemoveCommand(block);
	_undoStack->push(removeCommand);
}

void MapEditor::ReplaceBlock(osg::ref_ptr<Block> block, TexType type, FillType fType)
{
	QUndoCommand* replaceCommand = new ReplaceCommand(block, type, fType);
	_undoStack->push(replaceCommand);
}

void MapEditor::onClickedChangeSize()
{
	//resize map
	//if (!_undoStack->isClean()) _undoStack->clear();
	int mapSizeX = ui.spnBoxSizeX->value();
	int mapSizeZ = ui.spnBoxSizeZ->value();
	if (!(mapSizeX == _map->GetSizeX() / 16 && mapSizeZ == _map->GetSizeZ() / 16))
	{
		//push undoStack
		QUndoCommand* changeSizeCommand = new ChangeSizeCommand(_map,
			ui.spnBoxSizeX->value(), ui.spnBoxSizeZ->value());
		_undoStack->push(changeSizeCommand);
	}
}

void MapEditor::Undo()
{
	if (_undoStack->canUndo()) _undoStack->undo();
}