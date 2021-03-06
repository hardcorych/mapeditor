#pragma once
#include <RemoveCommand.h>

#include <Map.h>

RemoveCommand::RemoveCommand(Map& map,
                             int x,
                             int z, 
                             const BlockType& blockType, 
                             QUndoCommand* parent) :
  QUndoCommand(parent),
  _map(map),
  _x(x),
  _z(z),
  _blockType(blockType)
{
}

void RemoveCommand::undo()
{
  _map.AddBlock(_x, _z, _blockType);
}

void RemoveCommand::redo()
{
  _map.RemoveBlock(_x, _z);
}