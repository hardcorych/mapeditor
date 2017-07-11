#pragma once

#include <CreateBlockTypeEvent.h>
#include <DeleteBlockTypeCommand.h>
#include <DeleteBlockTypeEvent.h>
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
  QCoreApplication::postEvent(&_mapEditor,
                              new CreateBlockTypeEvent(_blockType));
}

void DeleteBlockTypeCommand::redo()
{
  _mapEditor.RemoveBlockType(_blockTypeId);
  QCoreApplication::postEvent(&_mapEditor,
                              new DeleteBlockTypeEvent(_blockTypeId));
}