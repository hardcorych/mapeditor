#pragma once

#include <DeleteBlockTypeCommand.h>
#include <DrawBlockPixmap.h>

DeleteBlockTypeCommand::DeleteBlockTypeCommand(const BlockType& blockType,
                                               int blockTypeId,
                                               MapEditor& mapEditor, 
                                               QUndoCommand* parent) :
  QUndoCommand(parent),
  _mapEditor(mapEditor),
  _blockType(blockType),
  _blockTypeId(blockTypeId)
{
}

DeleteBlockTypeCommand::~DeleteBlockTypeCommand()
{
}

void DeleteBlockTypeCommand::undo()
{
  _blockTypeId = _mapEditor.AddBlockType(_blockType);
}

void DeleteBlockTypeCommand::redo()
{
  _mapEditor.RemoveBlockType(_blockTypeId);
}