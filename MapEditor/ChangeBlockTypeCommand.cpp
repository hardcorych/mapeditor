#pragma once

#include <ChangeBlockTypeCommand.h>
#include <ChangeBlockTypeEvent.h>
#include <DrawBlockPixmap.h>

ChangeBlockTypeCommand::ChangeBlockTypeCommand(MapEditor::BlockTypes& blockTypes,
                                               const BlockType& blockType,
                                               const BlockType& blockTypeNew,
                                               MapEditor& mapEditor, 
                                               QUndoCommand* parent) :
  QUndoCommand(parent),
  _blockType(blockType),
  _blockTypeNew(blockTypeNew),
  _mapEditor(mapEditor),
  _blockTypes(blockTypes)
{
}

ChangeBlockTypeCommand::~ChangeBlockTypeCommand()
{
}

void ChangeBlockTypeCommand::undo()
{
  for (MapEditor::BlockTypes::iterator it = _blockTypes.begin();
       it != _blockTypes.end();
       ++it)
  {
    if (it->second == _blockTypeNew)
    {
      it->second = _blockType;  //change with old
      QCoreApplication::postEvent(&_mapEditor,
                                  new ChangeBlockTypeEvent(it->second));
      break;
    }
  }
}

void ChangeBlockTypeCommand::redo()
{
  for (MapEditor::BlockTypes::iterator it = _blockTypes.begin();
       it != _blockTypes.end();
       ++it)
  {
    if (it->second == _blockType)
    {
      it->second = _blockTypeNew; //change with new
      QCoreApplication::postEvent(&_mapEditor, 
                                  new ChangeBlockTypeEvent(it->second));
      break;
    }
  }
}