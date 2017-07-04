#pragma once

#include <RemoveCommand.h>

RemoveCommand::RemoveCommand(osg::ref_ptr<Map> map,
  int x, int z, BlockType blockType, QUndoCommand* parent) :
  QUndoCommand(parent),
  _map(map),
  _x(x), _z(z),
  _blockType(blockType)
{
  //_blockType = block->GetType();
}

RemoveCommand::~RemoveCommand()
{
}

void RemoveCommand::undo()
{
  //add
  //_block->SetType(_blockType);
  _map->AddBlock(_x, _z, _blockType);
}

void RemoveCommand::redo()
{
  //remove
  //BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);
  //_block->SetType(emptyBlock);
  _map->RemoveBlock(_x, _z);
}