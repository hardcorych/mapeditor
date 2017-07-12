#pragma once
#include "ReplaceCommand.h"

#include "Block.h"
#include "Map.h"

ReplaceCommand::ReplaceCommand(Map& map,
                               const Block& block,
                               const BlockType& blockType,
                               QUndoCommand* parent) :
  QUndoCommand(parent),
  _map(map),
  _blockType(blockType)
{
  _blockTypeOld = block.GetType();
  _x = block.GetX();
  _z = block.GetZ();
}

void ReplaceCommand::undo()
{
  //replace with old
  _map.AddBlock(_x, _z, _blockTypeOld);
}

void ReplaceCommand::redo()
{
  //replace with new
  _map.AddBlock(_x, _z, _blockType);
}