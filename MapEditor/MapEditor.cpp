#include "MapEditor.h"

#include <memory>

#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>

#include <qdebug.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qxmlstream.h>

#include <Commands.h>
#include <KeyboardMouseHandler.h>
#include <QBlockRadioButton.h>
#include <Viewer.h>

MapEditor::MapEditor(QWidget *parent)
  : QMainWindow(parent),
  _minMapSize(5),
  _maxMapSize(30)
{
  ui.setupUi(this);

  _fileMenu = new QMenu(this);
  _editMenu = new QMenu(this);
  _settingsMenu = new QMenu(this);

  _fileMenu->setTitle("&File");
  _editMenu->setTitle("&Edit");
  _settingsMenu->setTitle("&Settings");

  _newAct = new QAction(tr("&New"), this);
  _loadAct = new QAction(tr("&Load"), this);
  _saveAct = new QAction(tr("&Save"), this);
  _saveAsAct = new QAction(tr("&Save As"), this);

  _resizeMapAct = new QAction(tr("&Resize Map"), this);
  _blockEditAct = new QAction(tr("&Block Editor"), this);

  _undoStack = new QUndoStack(this);

  createUndoRedoActions();
  createUndoView();

  connect(_newAct, &QAction::triggered, this, &MapEditor::NewMap);
  connect(_loadAct, &QAction::triggered, this, &MapEditor::LoadXMLFile);
  connect(_saveAct, &QAction::triggered, this, &MapEditor::SaveXMLFile);
  connect(_saveAsAct, &QAction::triggered, this, &MapEditor::SaveAsXMLFile);

  //!!!
  connect(_resizeMapAct, &QAction::triggered, this, &MapEditor::changeMapSize);
  //connect(_blockEditAct)

  _fileMenu->addAction(_newAct);
  _fileMenu->addAction(_loadAct);
  _fileMenu->addAction(_saveAct);
  _saveAct->setDisabled(true);
  _fileMenu->addAction(_saveAsAct);

  _editMenu->addAction(_undoAct);
  _editMenu->addAction(_redoAct);

  _settingsMenu->addAction(_resizeMapAct);
  _settingsMenu->addAction(_blockEditAct);

  ui.menuBar->addMenu(_fileMenu);
  ui.menuBar->addMenu(_editMenu);
  ui.menuBar->addMenu(_settingsMenu);

  ui.labelMessage->setText("Information label");

  connect(ui.pushButtonCreateBlock, &QPushButton::clicked,
    this, &MapEditor::onClickedCreateButton);

  //??????
  connect(ui.radioBtnBushes, &QRadioButton::clicked, 
    this, &MapEditor::onClickedBushes);
  connect(ui.radioBtnWater, &QRadioButton::clicked,
    this, &MapEditor::onClickedWater);
  connect(ui.radioBtnIce, &QRadioButton::clicked,
    this, &MapEditor::onClickedIce);

  connect(ui.radioBtnArmorFull, &QRadioButton::clicked,
    this, &MapEditor::onClickedArmorFull);
  connect(ui.radioBtnArmorLeft, &QRadioButton::clicked,
    this, &MapEditor::onClickedArmorLeft);
  connect(ui.radioBtnArmorRight, &QRadioButton::clicked, 
    this, &MapEditor::onClickedArmorRight);
  connect(ui.radioBtnArmorBottom, &QRadioButton::clicked,
    this, &MapEditor::onClickedArmorBottom);
  connect(ui.radioBtnArmorTop, &QRadioButton::clicked,
    this, &MapEditor::onClickedArmorTop);

  connect(ui.radioBtnBrickFull, &QRadioButton::clicked,
    this, &MapEditor::onClickedBrickFull);
  connect(ui.radioBtnBrickLeft, &QRadioButton::clicked,
    this, &MapEditor::onClickedBrickLeft);
  connect(ui.radioBtnBrickRight, &QRadioButton::clicked,
    this, &MapEditor::onClickedBrickRight);
  connect(ui.radioBtnBrickBottom, &QRadioButton::clicked,
    this, &MapEditor::onClickedBrickBottom);
  connect(ui.radioBtnBrickTop, &QRadioButton::clicked,
    this, &MapEditor::onClickedBrickTop);

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

void MapEditor::onClickedCreateButton()
{
  QBlockRadioButton *rButton = new QBlockRadioButton(this);
  rButton->setText("izi");
  ui.gridLayout->addWidget(rButton, _row, _col++);
  if (_col == 6)
  {
    _col = 0;
    _row++;
  }
}

void MapEditor::SelectBlock()
{

}

void MapEditor::readTextures()
{

}

void MapEditor::NewMap()
{
  //создание новой карты через модальный диалог
  MapSizeDialog mapSizeDialog(this);

  if (mapSizeDialog.exec() == QDialog::Accepted)
  {
    int mapSizeX = mapSizeDialog.GetSizeX();
    int mapSizeZ = mapSizeDialog.GetSizeZ();
    createMap(mapSizeX, mapSizeZ);
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
  //—ƒ≈Ћј“№ ќЅ–јЅќ“ ” ќЎ»Ѕќ 
  /*
  _filename = QFileDialog::getOpenFileName(
    this, tr("Open XML"), ".",
    tr("XML files (*.xml)"));

  QFile file(_filename);

  if (!file.open(QIODevice::ReadOnly | QFile::Text))
  {
    //обработка ошибки?
    //QMessageBox::warning(this, "file error", "file can't be opened", QMessageBox::Ok);
  }
  else
  {
    if (!_undoStack->isClean()) _undoStack->clear();

    _saveAct->setDisabled(true);
    //file reading
    QXmlStreamReader xmlReader(&file);

    //for error output
    bool isError = false;
    QString errorText;

    bool isWrongType = false;
    bool isWrongFill = false;

    int mapSizeX = 0;
    int mapSizeZ = 0;

    while (!xmlReader.atEnd())
    {
      if (xmlReader.readNextStartElement())
      {
        QString element = xmlReader.name().toString();
        if (element == "sizeX")
        {
          mapSizeX = xmlReader.readElementText().toInt();
          if (mapSizeX < 0)
          {
            isError = true;
            errorText = "Negative map size X";
            break;
          }
          if (mapSizeX % 16 != 0)
          {
            isError = true;
            errorText = "Incorrect map size X: it's not multiple of 16";
            break;
          }
          if (mapSizeX < _minMapSize * 16 ||
            mapSizeX > _maxMapSize * 16)
          {
            isError = true;
            errorText = "Map size may be in range from "
              + QString::number(_minMapSize) +
              "to " + QString::number(_maxMapSize) + " blocks";
            break;
          }
          //get size in blocks
          mapSizeX /= 16;
        }
        else if (element == "sizeZ")
        {
          mapSizeZ = xmlReader.readElementText().toInt();
          if (mapSizeZ < 0)
          {
            isError = true;
            errorText = "Negative map size Z";
            break;
          }
          if (mapSizeZ % 16 != 0)
          {
            isError = true;
            errorText = "Incorrect map size Z: it's not multiple of 16";
            break;
          }
          if (mapSizeZ < _minMapSize * 16 ||
            mapSizeZ > _maxMapSize * 16)
          {
            isError = true;
            errorText = "Map size may be in range from " 
              + QString::number(_minMapSize) +
              "to " + QString::number(_maxMapSize) + " blocks";
            break;
          }
          //получаем размер в блоках
          mapSizeZ /= 16;
          createMap(mapSizeX, mapSizeZ);
        }
        else if (element == "block")
        {
          if (mapSizeX == 0 || mapSizeZ == 0)
          {
            isError = true;
            errorText = "There is no map size";
            break;
          }
          //чтение блока
          //чтение типа блока
          int x, z;
          //TexType texType;
          std::string typeName;
          std::string texPath;
          FillType fillType;

          int numAttributes = 0;

          if (xmlReader.attributes().size() != 2)
          {
            isError = true;
            errorText = "Incorrect number of block attributes";
            break;
          }

          for each (const QXmlStreamAttribute &attr in xmlReader.attributes())
          {
            QString attrStr = attr.name().toString();
            if (attrStr == "texType")
            {
              numAttributes++;
              std::string attrValue = attr.value().toString().toStdString();
              //!!!
              /*
              if (attrValue == "BORDER") texType = TexType::BORDER;
              else if (attrValue == "BRICK") texType = TexType::BRICK;
              else if (attrValue == "ARMOR") texType = TexType::ARMOR;
              else if (attrValue == "BUSHES") texType = TexType::BUSHES;
              else if (attrValue == "ICE") texType = TexType::ICE;
              else if (attrValue == "WATER") texType = TexType::WATER;
///////////////////////////////////////////////////////////////////////////////////
              if (_map->isFoundTexPath(attrValue))
              {
                texPath = attrValue;
              }
              else
              {
                isError = true;
                errorText = "Incorrect texType";
                break;
              }
            }
            else if (attrStr == "fillType")
            {
              numAttributes++;
              QString attrValue = attr.value().toString();
              //!!!
              if (attrValue == "BOTTOM") fillType = FillType::BOTTOM;
              else if (attrValue == "FULL") fillType = FillType::FULL;
              else if (attrValue == "LEFT") fillType = FillType::LEFT;
              else if (attrValue == "RIGHT") fillType = FillType::RIGHT;
              else if (attrValue == "TOP") fillType = FillType::TOP;
              else
              {
                isError = true;
                errorText = "Incorrect fillType";
                break;
              }
            }
          }

          //чтение координат
          int numCoords = 0;

          xmlReader.readNextStartElement();
          element = xmlReader.name().toString();
          if (element == "x")
          {
            numCoords++;
            x = xmlReader.readElementText().toInt();

            if (x < 0)
            {
              isError = true;
              errorText = "Negative X coordinate of block";
              break;
            }
            if (x % 16 != 0)
            {
              isError = true;
              errorText = "X block coordinate is not multiple of 16";
              break;
            }
            if (x > _maxMapSize * 16)
            {
              isError = true;
              errorText = "X coord may be in range of "
                + QString::number(_maxMapSize) + " blocks";
              break;
            }
            x -= 16;		//-16 for matching
          }

          xmlReader.readNextStartElement();
          element = xmlReader.name().toString();
          if (element == "z")
          {
            numCoords++;
            z = xmlReader.readElementText().toInt();

            if (z < 0)
            {
              isError = true;
              errorText = "Negative Z coordinate of block";
              break;
            }
            if (z % 16 != 0)
            {
              isError = true;
              errorText = "Z block coordinate is not multiple of 16";
              break;
            }
            if (z > _maxMapSize * 16)
            {
              isError = true;
              errorText = "Z coord may be in range of "
                + QString::number(_maxMapSize) + " blocks";
              break;
            }
            z -= 16;		//-16 for matching
          }


          if (numCoords != 2)
          {
            isError = true;
            errorText = "Incorrect number of block coordinates";
            break;
          }

          _map->AddBlock(new Block(x, z, texType, fillType), x, z);
        }
      }
    }
    file.close();

    //error message
    if (isError)
    {
      QMessageBox::critical(this, "File error", errorText, QMessageBox::Ok);
      _filename.clear();
      ui.labelMessage->setText("There were some errors while reading file.");
    }
    else
    {
      _saveAct->setEnabled(true);
      ui.labelMessage->setText("File was loaded successful.");
    }
  }
  */
}

void MapEditor::SaveXMLFile()
{
  /*
  if (_filename != "")
  {
    //сохранение файла по заданному пути
    QFile file(_filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();		//start a file writing

    //write map to xml
    xmlWriter.writeStartElement("map");

    xmlWriter.writeTextElement("sizeX", _map->GetSizeX_str());
    xmlWriter.writeTextElement("sizeZ", _map->GetSizeZ_str());

    osg::ref_ptr<Block> block = nullptr;
    osg::ref_ptr<Tile> tile = nullptr;

    std::pair<QString, QString> bTexFill;	//texture and fill block types

    for (int blockIndex = 0; blockIndex < _map->getNumChildren(); blockIndex++)
    {
      block = dynamic_cast<Block*>(_map->getChild(blockIndex));
      bTexFill = block->GetType_str();

      if (std::get<0>(bTexFill) != "EMPTY")	//empty blocks aren't written to file
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

    xmlWriter.writeEndDocument();		//end of file writing
    file.close();

    ui.labelMessage->setText("File was saved succesful.");
  }
  */
}

void MapEditor::SaveAsXMLFile()
{
  //диалог выбора дл€ сохранени€ файла
  _filename = QFileDialog::getSaveFileName(
    this, tr("Save XML"), ".",
    tr("XML files (*.xml)"));

  if (_filename != "")
  {
    SaveXMLFile();
    _saveAct->setEnabled(true);
  }
}

void MapEditor::onClickedBushes()
{
  emit SendBlockType(BlockType("BUSHES", _map->GetTexPath("BUSHES"),
    FillType::FULL, 1, 1));
}

void MapEditor::onClickedWater()
{
  emit SendBlockType(BlockType("WATER", _map->GetTexPath("WATER"),
    FillType::FULL, 1, 1));
}

void MapEditor::onClickedIce()
{
  emit SendBlockType(BlockType("ICE", _map->GetTexPath("ICE"),
    FillType::FULL, 1, 1));
}

void MapEditor::onClickedArmorFull()
{
  emit SendBlockType(BlockType("ARMOR", _map->GetTexPath("ARMOR"),
    FillType::FULL, 1, 1));
}

void MapEditor::onClickedArmorLeft()
{
  emit SendBlockType(BlockType("ARMOR", _map->GetTexPath("ARMOR"),
    FillType::LEFT, 1, 1));
}

void MapEditor::onClickedArmorRight()
{
  emit SendBlockType(BlockType("ARMOR", _map->GetTexPath("ARMOR"),
    FillType::RIGHT, 1, 1));
}

void MapEditor::onClickedArmorBottom()
{
  emit SendBlockType(BlockType("ARMOR", _map->GetTexPath("ARMOR"),
    FillType::BOTTOM, 1, 1));
}

void MapEditor::onClickedArmorTop()
{
  emit SendBlockType(BlockType("ARMOR", _map->GetTexPath("ARMOR"),
    FillType::TOP, 1, 1));
}

void MapEditor::onClickedBrickFull()
{
  emit SendBlockType(BlockType("BRICK", _map->GetTexPath("BRICK"),
    FillType::FULL, 1, 1));
}

void MapEditor::onClickedBrickLeft()
{
  emit SendBlockType(BlockType("BRICK", _map->GetTexPath("BRICK"),
    FillType::LEFT, 1, 1));
}

void MapEditor::onClickedBrickRight()
{
  emit SendBlockType(BlockType("BRICK", _map->GetTexPath("BRICK"),
    FillType::RIGHT, 1, 1));
}

void MapEditor::onClickedBrickBottom()
{
  emit SendBlockType(BlockType("BRICK", _map->GetTexPath("BRICK"),
    FillType::BOTTOM, 1, 1));
}

void MapEditor::onClickedBrickTop()
{
  emit SendBlockType(BlockType("BRICK", _map->GetTexPath("BRICK"),
    FillType::TOP, 1, 1));
}

void MapEditor::renderScene()
{
  Viewer viewer;

  connect(this, &MapEditor::QuitViewer, 
    &viewer, &Viewer::onQuitViewer, Qt::DirectConnection);

  //настройка окна
  int xViewer = 100;
  int yViewer = 100;
  int wViewer = 640;
  int hViewer = 480;

  viewer.setUpViewInWindow(xViewer, yViewer, wViewer, hViewer);

  viewer.realize();

  osg::ref_ptr<KeyboardMouseHandler> keyboardMouseHandler = 
    new KeyboardMouseHandler;
  viewer.addEventHandler(keyboardMouseHandler);
  viewer.addEventHandler(new osgViewer::StatsHandler);

  connect(this, &MapEditor::SendBlockType, keyboardMouseHandler,
    &KeyboardMouseHandler::ReceiveBlock, Qt::DirectConnection);
  connect(keyboardMouseHandler, &KeyboardMouseHandler::AddableBlock, 
    this, &MapEditor::AddBlock, Qt::DirectConnection);
  connect(keyboardMouseHandler, &KeyboardMouseHandler::RemovableBlock, 
    this, &MapEditor::RemoveBlock, Qt::DirectConnection);
  connect(keyboardMouseHandler, &KeyboardMouseHandler::ReplaceableBlock, 
    this, &MapEditor::ReplaceBlock, Qt::DirectConnection);
  connect(keyboardMouseHandler, &KeyboardMouseHandler::Undo,
    _undoStack, &QUndoStack::undo);
  connect(keyboardMouseHandler, &KeyboardMouseHandler::Redo,
    _undoStack, &QUndoStack::redo);

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
    //std::lock_guard<std::mutex> lgMutex(_mutex);	
    //дл€ избежани€ конфликта при создании новой карты
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

void MapEditor::AddBlock(osg::ref_ptr<Block> block, 
  BlockType blockType)
{
  QUndoCommand* addCommand = new AddCommand(block, blockType);
  _undoStack->push(addCommand);
}

void MapEditor::RemoveBlock(osg::ref_ptr<Block> block)
{
  QUndoCommand* removeCommand = new RemoveCommand(block);
  _undoStack->push(removeCommand);
}

void MapEditor::ReplaceBlock(osg::ref_ptr<Block> block, 
  BlockType blockType)
{
  QUndoCommand* replaceCommand = new ReplaceCommand(block, blockType);
  _undoStack->push(replaceCommand);
}

void MapEditor::changeMapSize()
{
  //resize map
  MapSizeDialog mapSizeDialog(this);

  if (mapSizeDialog.exec() == QDialog::Accepted)
  {
    int mapSizeX = mapSizeDialog.GetSizeX();
    int mapSizeZ = mapSizeDialog.GetSizeZ();

    if (!(mapSizeX == _map->GetSizeX() / 16 && 
      mapSizeZ == _map->GetSizeZ() / 16))
    {
      //push undoStack
      QUndoCommand* changeSizeCommand = 
        new ChangeSizeCommand(_map, mapSizeX, mapSizeZ);
      _undoStack->push(changeSizeCommand);
    }
  }

}

void MapEditor::Undo()
{
  if (_undoStack->canUndo()) _undoStack->undo();
}