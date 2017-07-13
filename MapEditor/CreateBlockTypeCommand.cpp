#pragma once
#include <CreateBlockTypeCommand.h>

#include <qpainter.h>

#include <CreateBlockTypeEvent.h>
#include <DeleteBlockTypeEvent.h>
#include <DrawBlockPixmap.h>

CreateBlockTypeCommand::CreateBlockTypeCommand(MapEditor::BlockTypes& blockTypes,
                                               const BlockType& blockType, 
                                               MapEditor& mapEditor, 
                                               QUndoCommand* parent) :
  QUndoCommand(parent),
  _blockType(blockType),
  _mapEditor(mapEditor),
  _blockTypeId(0),
  _blockTypes(blockTypes)
{
}

void CreateBlockTypeCommand::undo()
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

void CreateBlockTypeCommand::redo()
{
  _blockTypeId = _mapEditor.AddBlockType(_blockType);
  QCoreApplication::postEvent(&_mapEditor, 
                              new CreateBlockTypeEvent(_blockType));
}