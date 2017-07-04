#pragma once

#include <qpainter.h>

#include <CreateBlockTypeCommand.h>
#include <DrawBlockPixmap.h>

CreateBlockTypeCommand::CreateBlockTypeCommand(QButtonGroup* btnGroup,
  BlockType blockType, MapEditor* mapEditor, QUndoCommand* parent) :
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