#include "MapEditor.h"

#include <memory>

#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>

#include <qdebug.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qxmlstream.h>

#include <BlockEditDialog.h>
#include <Commands.h>
#include <KeyboardMouseHandler.h>
#include <MapSizeDialog.h>
#include <Viewer.h>

MapEditor::MapEditor(QWidget *parent)
  : QMainWindow(parent),
  _minMapSize(5),
  _maxMapSize(30)
{
  ui.setupUi(this);

  _btnGroupBlocks = new QButtonGroup(this);

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
  connect(_blockEditAct, &QAction::triggered, this, &MapEditor::blockEdit);

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

  connect(_btnGroupBlocks,
    static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
    [=](int id)
  {
    emit SendBlockType(_blockTypes[id]);
  });

  _renderThread = std::thread(&MapEditor::renderScene, this);
  
  //setting default texture paths
  _texPaths["BORDER"] = "Resources/tiles/BORDER.png";
  _texPaths["ARMOR"] = "Resources/tiles/ARMOR.png";
  _texPaths["BRICK"] = "Resources/tiles/BRICK.png";
  _texPaths["BUSHES"] = "Resources/tiles/BUSHES.png";
  _texPaths["ICE"] = "Resources/tiles/ICE.png";
  _texPaths["WATER"] = "Resources/tiles/WATER.png";

  //setting default blocktypes
  _blockTypes[-2] = BlockType("BUSHES", _texPaths["BUSHES"],
    "FULL", 0, 0);
  _blockTypes[-3] = BlockType("WATER", _texPaths["WATER"],
    "FULL", 0, 0);
  _blockTypes[-4] = BlockType("ICE", _texPaths["ICE"],
    "FULL", 0, 0);

  _blockTypes[-5] = BlockType("ARMOR", _texPaths["ARMOR"],
    "FULL", 0, 0);
  _blockTypes[-6] = BlockType("ARMOR", _texPaths["ARMOR"],
    "LEFT", 0, 0);
  _blockTypes[-7] = BlockType("ARMOR", _texPaths["ARMOR"],
    "RIGHT", 0, 0);
  _blockTypes[-8] = BlockType("ARMOR", _texPaths["ARMOR"],
    "TOP", 0, 0);
  _blockTypes[-9] = BlockType("ARMOR", _texPaths["ARMOR"],
    "BOTTOM", 0, 0);

  _blockTypes[-10] = BlockType("BRICK", _texPaths["BRICK"],
    "FULL", 0, 0);
  _blockTypes[-11] = BlockType("BRICK", _texPaths["BRICK"],
    "LEFT", 0, 0);
  _blockTypes[-12] = BlockType("BRICK", _texPaths["BRICK"],
    "RIGHT", 0, 0);
  _blockTypes[-13] = BlockType("BRICK", _texPaths["BRICK"],
    "TOP", 0, 0);
  _blockTypes[-14] = BlockType("BRICK", _texPaths["BRICK"],
    "BOTTOM", 0, 0);

  //setting blocktypes buttons
  _col = -1;

  for (std::map<int, BlockType>::iterator it = _blockTypes.begin();
    it != _blockTypes.end(); ++it)
  {
    QRadioButton *rButton = new QRadioButton(this);
    _btnGroupBlocks->addButton(rButton);
    int btnId = _btnGroupBlocks->id(rButton);   //-2, -3, etc...

    QPixmap pixmap = DrawBlockPixmap(_blockTypes[btnId]);
    rButton->setIconSize(QSize(64, 64));
    rButton->setIcon(pixmap);

    if (++_col == _maxColumnElements)
    {
      _col = 0;
      _row++;
    }

    ui.gridLayout->addWidget(rButton, _row, _col);
    rButton->setVisible(true);
  }
}

MapEditor::~MapEditor()
{
  if (_renderThread.joinable())
  {
    emit QuitViewer();
    _renderThread.join();
  }
}

void MapEditor::CreateBlockType(QButtonGroup* btnGroup,
  BlockType blockType)
{
  QUndoCommand* createBlockTypeCommand =
    new CreateBlockTypeCommand(btnGroup, blockType, this);
  _undoStack->push(createBlockTypeCommand);
}

void MapEditor::ChangeBlockType(QAbstractButton* rButton, 
  BlockType& blockType, BlockType blockTypeNew)
{
  QUndoCommand* changeBlockTypeCommand =
    new ChangeBlockTypeCommand(rButton, blockType, blockTypeNew,
    this);
  _undoStack->push(changeBlockTypeCommand);
}

void MapEditor::DeleteBlockType(QAbstractButton* button,
  BlockType blockType)
{
  QUndoCommand* deleteBlockTypeCommand =
    new DeleteBlockTypeCommand(_btnGroupBlocks, blockType, this);
  _undoStack->push(deleteBlockTypeCommand);
}

void MapEditor::AddBlockType(int id, BlockType blockType)
{
  _blockTypes[id] = blockType;
  if (_texPaths.find(blockType.GetTypeName()) == _texPaths.end())
  {
    _texPaths[blockType.GetTypeName()] = blockType.GetTexPath();
  }
}

void MapEditor::AddBlockTypeButton(QRadioButton* rButton, int& row, int& col)
{
  if (col == _maxColumnElements)
  {
    col = 0;
    row++;
  }

  ui.gridLayout->addWidget(rButton, row, col);
  rButton->setVisible(true);
}

void MapEditor::GetButtonRowCol(QRadioButton* rButton, int& row, int& col)
{
  int widgetIndex = ui.gridLayout->indexOf(rButton);
  int rowSpan, colSpan;
  ui.gridLayout->getItemPosition(widgetIndex, &row, &col,
    &rowSpan, &colSpan);
}

std::pair<int, int> MapEditor::GetNextRowCol()
{
  if (++_col == _maxColumnElements)
  {
    _col = 0;
    _row++;
  }
  return std::make_pair(_row, _col);
}

void MapEditor::SetPrevRowCol()
{
  if (--_col < 0)
  {
    _col = _maxColumnElements - 1;
    _row--;
  }
}

void MapEditor::RemoveBlockType(int id)
{
  _blockTypes.erase(id);
}

void MapEditor::RemoveBlockTypeButton(QRadioButton* rButton)
{
  rButton->hide();

  ui.gridLayout->removeWidget(rButton);
  _btnGroupBlocks->removeButton(rButton);
  
  delete rButton;
}

void MapEditor::blockEdit()
{
  int blockTypeId = _btnGroupBlocks->checkedId();
  BlockType blockType = _blockTypes[blockTypeId];
  BlockEditDialog blockEditDialog(this, blockType);
  BlockType newBlockType;

  QString newBlockName;

  QRadioButton* rButton;

  QPixmap pixmap;

  //processing of dialog action
  switch (blockEditDialog.exec())
  {
  case (int)BlockEditAction::CREATE:
    CreateBlockType(_btnGroupBlocks, blockEditDialog.GetBlockType());
    break;

  case (int)BlockEditAction::CHANGE:
    if (_btnGroupBlocks->checkedButton() != 0)
    {
      ChangeBlockType(_btnGroupBlocks->checkedButton(),
        _blockTypes[blockTypeId], blockEditDialog.GetBlockType());
    }
    else
    {
      QMessageBox::critical(this, "Error",
        "Block type is not selected", QMessageBox::Ok);
    }
    break;

  case (int)BlockEditAction::DELETE:
    if (_btnGroupBlocks->checkedButton() != 0)
    {
      DeleteBlockType(_btnGroupBlocks->checkedButton(),
        _blockTypes[_btnGroupBlocks->checkedId()]);
    }
    else
    {
      QMessageBox::critical(this, "Error", 
        "Block type is not selected", QMessageBox::Ok);
    }
    break;
  }
}

void MapEditor::NewMap()
{
  //create new map by modal dialog
  MapSizeDialog mapSizeDialog(this);

  if (mapSizeDialog.exec() == QDialog::Accepted)
  {
    int mapSizeX = mapSizeDialog.GetSizeX();
    int mapSizeZ = mapSizeDialog.GetSizeZ();
    createMap(mapSizeX, mapSizeZ);
    if (!_undoStack->isClean()) _undoStack->clear();

    _saveAct->setDisabled(true);
  }
}

void MapEditor::createMap(int sizeX, int sizeZ)
{
  _map->Remove();
  _map->Set(sizeX, sizeZ);
}

void MapEditor::LoadXMLFile()
{  
  _filename = QFileDialog::getOpenFileName(
    this, tr("Open XML"), ".",
    tr("XML files (*.xml)"));

  QFile file(_filename);

  if (!file.open(QIODevice::ReadOnly | QFile::Text))
  {
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
          if (mapSizeX % _blockSize != 0)
          {
            isError = true;
            errorText = "Incorrect map size X: it's not multiple of 16";
            break;
          }
          if (mapSizeX < _minMapSize * _blockSize ||
            mapSizeX > _maxMapSize * _blockSize)
          {
            isError = true;
            errorText = "Map size may be in range from "
              + QString::number(_minMapSize) +
              "to " + QString::number(_maxMapSize) + " blocks";
            break;
          }
          //get size in blocks
          mapSizeX /= _blockSize;
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
          if (mapSizeZ % _blockSize != 0)
          {
            isError = true;
            errorText = "Incorrect map size Z: it's not multiple of 16";
            break;
          }
          if (mapSizeZ < _minMapSize * _blockSize ||
            mapSizeZ > _maxMapSize * _blockSize)
          {
            isError = true;
            errorText = "Map size may be in range from " 
              + QString::number(_minMapSize) +
              "to " + QString::number(_maxMapSize) + " blocks";
            break;
          }
          //�������� ������ � ������
          mapSizeZ /= _blockSize;
          //!!!
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
          //������ �����
          //������ ���� �����
          int x, z;

          BlockType blockType;

          int numAttributes = 0;

          if (xmlReader.attributes().size() < 2 ||
            xmlReader.attributes().size() > 4)
          {
            isError = true;
            errorText = "Incorrect number of block attributes";
            break;
          }

          bool isBorder = false;

          for each (const QXmlStreamAttribute &attr in xmlReader.attributes())
          {
            QString attrStr = attr.name().toString();
            if (attrStr == "texType")
            {
              numAttributes++;
              std::string attrValue = attr.value().toString().toStdString();
              //!!!
              if (attrValue == "BORDER")
              {
                isBorder = true;
                break;
              }
              bool isTypeFound = false;
              for (std::map<int, BlockType>::iterator it = _blockTypes.begin();
                it != _blockTypes.end(); ++it)
              {
                if (attrValue == it->second.GetTypeName())
                {
                  isTypeFound = true;
                  break;
                }
              }

              if (isTypeFound)
              {
                blockType.SetTypeName(attrValue);
                //����������� ���� ����� ��������
                blockType.SetTexPath(_texPaths[attrValue]);
              }
              else
              {
                isError = true;
                errorText = "Incorrect texType";
                break;
              }
            }
            else if (attrStr == "fillType" && !isBorder)
            {
              numAttributes++;
              QString attrValue = attr.value().toString();

              if (attrValue != "BOTTOM" && attrValue != "FULL" &&
                attrValue != "LEFT" && attrValue != "RIGHT" &&
                attrValue != "TOP")
              {
                isError = true;
                errorText = "Incorrect fillType";
                break;
              }
              else
              {
                blockType.SetFillType(attrValue.toStdString());
              }
            }
            else if (attrStr == "isPassable" && !isBorder)
            {
              numAttributes++;
              QString attrValue = attr.value().toString();

              if (attrValue == "true")
              {
                blockType.SetPassability(true);
              }
              else if (attrValue == "false")
              {
                blockType.SetPassability(false);
              }
              else
              {
                isError = true;
                errorText = "Passability may be true or false";
                break;
              }
            }
            else if (attrStr == "isUnderTank" && !isBorder)
            {
              numAttributes++; 
              QString attrValue = attr.value().toString();

              if (attrValue == "true")
              {
                blockType.SetUnderTank(true);
              }
              else if (attrValue == "false")
              {
                blockType.SetUnderTank(false);
              }
              else
              {
                isError = true;
                errorText = "UnderTank parameter may be true or false";
                break;
              }
            }
          }

          if (!isBorder)
          {
            //������ ���������
            int numCoords = 0;

            //x coord
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
              if (x % _blockSize != 0)
              {
                isError = true;
                errorText = "X block coordinate is not multiple of 16";
                break;
              }
              if (x > _maxMapSize * _blockSize)
              {
                isError = true;
                errorText = "X coord may be in range of "
                  + QString::number(_maxMapSize) + " blocks";
                break;
              }
              x -= _blockSize;		//-16 for matching
            }

            //z coord
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
              if (z % _blockSize != 0)
              {
                isError = true;
                errorText = "Z block coordinate is not multiple of 16";
                break;
              }
              if (z > _maxMapSize * _blockSize)
              {
                isError = true;
                errorText = "Z coord may be in range of "
                  + QString::number(_maxMapSize) + " blocks";
                break;
              }
              z -= _blockSize;		//-16 for matching
            }


            if (numCoords != 2)
            {
              isError = true;
              errorText = "Incorrect number of block coordinates";
              break;
            }

            //add read block
            _map->AddBlock(new Block(x, z, blockType));
          }
          
        }
      }
    }
    file.close();

    //error message
    if (isError)
    {
      QMessageBox::critical(this, "File error", errorText, QMessageBox::Ok);
      _filename.clear();
      _map->Remove();
      ui.labelMessage->setText("There were some errors while reading file.");
    }
    else
    {
      _saveAct->setEnabled(true);
      ui.labelMessage->setText("File was loaded successful.");
    }
  }
  
}

void MapEditor::SaveXMLFile()
{
  
  if (_filename != "")
  {
    //���������� ����� �� ��������� ����
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

    for (int blockIndex = 0; blockIndex < _map->getNumChildren(); blockIndex++)
    {
      block = dynamic_cast<Block*>(_map->getChild(blockIndex));
      BlockType blockType = block->GetType();

      if (blockType.GetTypeName() != "EMPTY")	//empty blocks aren't written to file
      {
        xmlWriter.writeStartElement("block");
        xmlWriter.writeAttribute("texType", QString::
          fromStdString(blockType.GetTypeName()));
        xmlWriter.writeAttribute("fillType", QString::
          fromStdString(blockType.GetFillType()));

        if (blockType.GetPassability())
        {
          xmlWriter.writeAttribute("isPassable", "true");
        }
        else
        {
          xmlWriter.writeAttribute("isPassable", "false");
        }

        if (blockType.GetUnderTank())
        {
          xmlWriter.writeAttribute("isUnderTank", "true");
        }
        else
        {
          xmlWriter.writeAttribute("isUnderTank", "false");
        }

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
  
}

void MapEditor::SaveAsXMLFile()
{
  //������ ������ ��� ���������� �����
  _filename = QFileDialog::getSaveFileName(
    this, tr("Save XML"), ".",
    tr("XML files (*.xml)"));

  if (_filename != "")
  {
    SaveXMLFile();
    _saveAct->setEnabled(true);
  }
}


void MapEditor::renderScene()
{
  Viewer viewer;

  connect(this, &MapEditor::QuitViewer, 
    &viewer, &Viewer::onQuitViewer, Qt::DirectConnection);

  //��������� ����
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

  viewer.setSceneData(_map);
  viewer.setCameraManipulator(new osgGA::TrackballManipulator);

  //viewer.getCamera()->setClearColor(osg::Vec4(0., 0., 0., 0.));

  viewer.realize();
  /////////////////////////////
  //viewer.run();

  while (!viewer.done())
  {	
    //��� ��������� ��������� ��� �������� ����� �����
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

    if (!(mapSizeX == _map->GetSizeX() / _blockSize && 
      mapSizeZ == _map->GetSizeZ() / _blockSize))
    {
      //push undoStack
      QUndoCommand* changeSizeCommand = 
        new ChangeSizeCommand(_map, mapSizeX, mapSizeZ);
      _undoStack->push(changeSizeCommand);
    }
  }

}