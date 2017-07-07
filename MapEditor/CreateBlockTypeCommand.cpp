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
{
}

CreateBlockTypeCommand::~CreateBlockTypeCommand()
{
}

void CreateBlockTypeCommand::undo()
{
  _mapEditor.RemoveBlockType(_blockTypeId);
}

void CreateBlockTypeCommand::redo()
{
  _blockTypeId = _mapEditor.AddBlockType(_blockType);
}