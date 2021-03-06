#pragma once
#include <AddCommand.h>

#include <Map.h>

AddCommand::AddCommand(Map& map,
                       int x,
                       int z,
                       const BlockType& blockType, 
                       QUndoCommand* parent) :
  QUndoCommand(parent),
  _x(x),
  _z(z),
  _blockType(blockType),
  _map(map)
{
}

void AddCommand::undo()
{
  _map.RemoveBlock(_x, _z);
}

void AddCommand::redo()
{
  _map.AddBlock(_x, _z, _blockType);
}