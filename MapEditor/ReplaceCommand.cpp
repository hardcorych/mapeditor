#pragma once

#include <ReplaceCommand.h>

ReplaceCommand::ReplaceCommand(osg::ref_ptr<Map> map,
                               osg::ref_ptr<Block> block,
                               const BlockType& blockType,
                               QUndoCommand* parent) :
  QUndoCommand(parent),
  _map(map),
  _blockType(blockType)
{
  _blockTypeOld = block->GetType();
  _x = block->GetX();
  _z = block->GetZ();
}

ReplaceCommand::~ReplaceCommand()
{
}

void ReplaceCommand::undo()
{
  //replace with old
  _map->AddBlock(_x, _z, _blockTypeOld);
}

void ReplaceCommand::redo()
{
  //replace with new
  _map->AddBlock(_x, _z, _blockType);
}