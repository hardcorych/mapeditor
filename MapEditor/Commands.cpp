#pragma once

#include <qpainter.h>

#include <Commands.h>
#include <MapEditor.h>

//AddCommand

AddCommand::AddCommand(osg::ref_ptr<Block> block, 
  BlockType blockType, QUndoCommand* parent) :
QUndoCommand(parent),
_block(block),
_blockType(blockType)
{
}

AddCommand::~AddCommand()
{
}

void AddCommand::undo()
{
  //remove
  BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);
  _block->SetType(emptyBlock);
}

void AddCommand::redo()
{
  //add
  _block->SetType(_blockType);
}

//ReplaceCommand

ReplaceCommand::ReplaceCommand(osg::ref_ptr<Block> block,
  BlockType blockType, QUndoCommand* parent) :
QUndoCommand(parent),
_block(block),
_blockType(blockType)
{
  _blockTypeOld = block->GetType();
}

ReplaceCommand::~ReplaceCommand()
{
}

void ReplaceCommand::undo()
{
  //replace with old
  _block->SetType(_blockTypeOld);
}

void ReplaceCommand::redo()
{
  //replace with new
  _block->SetType(_blockType);
}

//RemoveCommand

RemoveCommand::RemoveCommand(osg::ref_ptr<Block> block, QUndoCommand* parent) :
QUndoCommand(parent),
_block(block)
{
  _blockType = block->GetType();
}

RemoveCommand::~RemoveCommand()
{
}

void RemoveCommand::undo()
{
  //add
  _block->SetType(_blockType);
}

void RemoveCommand::redo()
{
  //remove
  BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);
  _block->SetType(emptyBlock);
}

//ChangeSizeCommand

ChangeSizeCommand::ChangeSizeCommand(osg::ref_ptr<Map> map, 
  int mapSizeX, int mapSizeZ, QUndoCommand* parent) :
QUndoCommand(parent)
{
  _map = map;
  _mapSizeX = mapSizeX;
  _mapSizeZ = mapSizeZ;
  _mapSizeXOld = _map->GetSizeX() / 16;
  _mapSizeZOld = _map->GetSizeZ() / 16;
}

ChangeSizeCommand::~ChangeSizeCommand()
{
}

void ChangeSizeCommand::undo()
{
  //set old map
  deletedBlocks = _map->Resize(deletedBlocks, _mapSizeXOld, _mapSizeZOld);
}

void ChangeSizeCommand::redo()
{
  //set new map size
  deletedBlocks = _map->Resize(deletedBlocks, _mapSizeX, _mapSizeZ);
}

//CreateBlockTypeCommand
CreateBlockTypeCommand::CreateBlockTypeCommand(QButtonGroup* btnGroup,
  BlockType blockType, MapEditor* mapEditor, QUndoCommand* parent):
  QUndoCommand(parent),
  _blockType(blockType),
  _mapEditor(mapEditor),
  _btnGroup(btnGroup)
{
}

CreateBlockTypeCommand::~CreateBlockTypeCommand()
{
}

void CreateBlockTypeCommand::undo()
{
  _mapEditor->RemoveBlockType(_btnGroup->id(_button));
  _mapEditor->RemoveBlockTypeButton(_button);

  _mapEditor->SetPrevRowCol();

  emit _mapEditor->SendBlockType(BlockType());
}

void CreateBlockTypeCommand::redo()
{
  _button = new QRadioButton;
  _button->setIconSize(QSize(64, 64));

  QPixmap pixmap = DrawBlockPixmap(_blockType);
  _button->setIcon(pixmap);
  _btnGroup->addButton(_button);

  _mapEditor->AddBlockType(_btnGroup->id(_button), _blockType);

  std::pair<int, int> rowCol = _mapEditor->GetNextRowCol();
  _row = rowCol.first;
  _col = rowCol.second;

  _mapEditor->AddBlockTypeButton(_button, _row, _col);
}

//ChangeBlockTypeCommand
ChangeBlockTypeCommand::ChangeBlockTypeCommand(QAbstractButton* button,
  BlockType& blockType, BlockType blockTypeNew,
  MapEditor* mapEditor, QUndoCommand* parent) :
  QUndoCommand(parent),
  _blockTypeRef(blockType),
  _blockType(blockType),
  _blockTypeNew(blockTypeNew),
  _button(button),
  _mapEditor(mapEditor)
{
  _button->setIconSize(QSize(64, 64));
}

ChangeBlockTypeCommand::~ChangeBlockTypeCommand()
{
}

void ChangeBlockTypeCommand::undo()
{
  _blockTypeRef = _blockType;
  QPixmap pixmap = DrawBlockPixmap(_blockType);
  _button->setIcon(pixmap);

  emit _mapEditor->SendBlockType(_blockType);
}

void ChangeBlockTypeCommand::redo()
{
  _blockTypeRef = _blockTypeNew;
  QPixmap pixmap = DrawBlockPixmap(_blockTypeNew);
  _button->setIcon(pixmap);

  emit _mapEditor->SendBlockType(_blockTypeNew);
}

QPixmap DrawBlockPixmap(BlockType blockType)
{
  QPixmap pixmap(QSize(32, 32));
  QPixmap pixmapResult(QSize(32, 32));
  QPainter painter(&pixmapResult);

  pixmap.load(QString::fromStdString(blockType.GetTexPath()));
  int height = 16;
  int width = 16;

  std::string fillType = blockType.GetFillType();
  if (fillType == "FULL")
  {
    painter.drawPixmap(QRect(0, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(0, height, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, height, width, height), pixmap, pixmap.rect());
  }
  else if (fillType == "LEFT")
  {
    painter.drawPixmap(QRect(0, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(0, height, width, height), pixmap, pixmap.rect());
  }
  else if (fillType == "RIGHT")
  {
    painter.drawPixmap(QRect(width, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, height, width, height), pixmap, pixmap.rect());
  }
  else if (fillType == "BOTTOM")
  {
    painter.drawPixmap(QRect(0, height, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, height, width, height), pixmap, pixmap.rect());
  }
  else if (fillType == "TOP")
  {
    painter.drawPixmap(QRect(0, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, 0, width, height), pixmap, pixmap.rect());
  }

  return pixmapResult;
}

DeleteBlockTypeCommand::DeleteBlockTypeCommand(QButtonGroup* btnGroup,
  BlockType blockType, MapEditor* mapEditor, QUndoCommand* parent) :
QUndoCommand(parent),
_btnGroup(btnGroup),
_mapEditor(mapEditor),
_blockType(blockType)
{
  _button = 
    qobject_cast<QRadioButton*>(_btnGroup->checkedButton());
  _buttonId = _btnGroup->checkedId();
  _mapEditor->GetButtonRowCol(_button, _row, _col);
}

DeleteBlockTypeCommand::~DeleteBlockTypeCommand()
{
}

void DeleteBlockTypeCommand::undo()
{
  _button = new QRadioButton;
  _button->setIconSize(QSize(64, 64));

  QPixmap pixmap = DrawBlockPixmap(_blockType);
  _button->setIcon(pixmap);
  _btnGroup->addButton(_button);

  _mapEditor->AddBlockType(_btnGroup->id(_button), _blockType);
  _mapEditor->AddBlockTypeButton(_button, _row, _col);
}

void DeleteBlockTypeCommand::redo()
{
  _mapEditor->RemoveBlockType(_buttonId);
  //_button = qobject_cast<QRadioButton*>(_btnGroup->checkedButton());
  _mapEditor->RemoveBlockTypeButton(_button);
  emit _mapEditor->SendBlockType(BlockType());
}