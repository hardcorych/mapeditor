#pragma once

#include <DeleteBlockTypeCommand.h>
#include <DrawBlockPixmap.h>

DeleteBlockTypeCommand::DeleteBlockTypeCommand(const BlockType& blockType,
                                               int blockTypeId,
                                               MapEditor& mapEditor, 
                                               QUndoCommand* parent) :
  QUndoCommand(parent),
  //_btnGroup(btnGroup),
  _mapEditor(mapEditor),
  _blockType(blockType),
  _blockTypeId(blockTypeId)
{
  /*
  _button =
    qobject_cast<QRadioButton*>(_btnGroup->checkedButton());
  _buttonId = _btnGroup->checkedId();
  _mapEditor->GetButtonRowCol(_button, _row, _col);
  */
}

DeleteBlockTypeCommand::~DeleteBlockTypeCommand()
{
}

void DeleteBlockTypeCommand::undo()
{
  _blockTypeId = _mapEditor.AddBlockType(_blockType);
  //_button = new QRadioButton;
  //_button->setIconSize(QSize(64, 64));

  //QPixmap pixmap = DrawBlockPixmap(_blockType);
  //_button->setIcon(pixmap);
  //_btnGroup->addButton(_button);

  //_mapEditor->AddBlockType(_btnGroup->id(_button), _blockType);
  //_mapEditor->AddBlockTypeButton(_button, _row, _col);
}

void DeleteBlockTypeCommand::redo()
{
  _mapEditor.RemoveBlockType(_blockTypeId);
  //_mapEditor->RemoveBlockType(_buttonId);
  //_mapEditor->RemoveBlockTypeButton(_button);
}