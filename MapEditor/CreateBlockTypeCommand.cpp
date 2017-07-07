#pragma once

#include <qpainter.h>

#include <CreateBlockTypeCommand.h>
#include <DrawBlockPixmap.h>

CreateBlockTypeCommand::CreateBlockTypeCommand(const BlockType& blockType, 
                                               MapEditor& mapEditor, 
                                               QUndoCommand* parent) :
    QUndoCommand(parent),
    _blockType(blockType),
    _mapEditor(mapEditor),
    _blockTypeId(0)
    //_btnGroup(btnGroup)
{
}

CreateBlockTypeCommand::~CreateBlockTypeCommand()
{
}

void CreateBlockTypeCommand::undo()
{
  _mapEditor.RemoveBlockType(_blockTypeId);
  //_mapEditor.RemoveBlockType(_btnGroup->id(_button));
  //_mapEditor.RemoveBlockTypeButton(_button);

  //_mapEditor.SetPrevRowCol();
}

void CreateBlockTypeCommand::redo()
{
  _blockTypeId = _mapEditor.AddBlockType(_blockType);
  //_button = new QRadioButton;
  //_button->setIconSize(QSize(64, 64));

  //QPixmap pixmap = DrawBlockPixmap(_blockType);
  //_button->setIcon(pixmap);
  //_btnGroup->addButton(_button);

  //_mapEditor->AddBlockType(_btnGroup->id(_button), _blockType);

  //_mapEditor->GetNextRowCol(_row, _col);

  //_mapEditor->AddBlockTypeButton(_button, _row, _col);
}