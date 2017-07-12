#pragma once
#include "DeleteBlockTypeCommand.h"


#include "CreateBlockTypeEvent.h"
#include "DeleteBlockTypeEvent.h"
#include "DrawBlockPixmap.h"

DeleteBlockTypeCommand::DeleteBlockTypeCommand(MapEditor::BlockTypes& blockTypes,
                                               const BlockType& blockType,
                                               int blockTypeId,
                                               MapEditor& mapEditor, 
                                               QUndoCommand* parent) :
  QUndoCommand(parent),
  _mapEditor(mapEditor),
  _blockType(blockType),
  _blockTypeId(blockTypeId),
  _blockTypes(blockTypes)
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
  for (MapEditor::BlockTypes::iterator it = _blockTypes.begin();
    it != _blockTypes.end();
    ++it)
  {
    if (it->second == _blockType)
    {
      _blockTypeId = it->first;
      break;
    }
  }
  _mapEditor.DeleteBlockType(_blockTypeId);
  QCoreApplication::postEvent(&_mapEditor,
                              new DeleteBlockTypeEvent(_blockTypeId));
}