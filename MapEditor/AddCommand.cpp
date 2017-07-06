#pragma once

#include <AddCommand.h>

AddCommand::AddCommand(osg::ref_ptr<Map> map,
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

AddCommand::~AddCommand()
{
}

void AddCommand::undo()
{
  //remove
  //BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);
  //_block->SetType(emptyBlock);
  _map->RemoveBlock(_x, _z);
}

void AddCommand::redo()
{
  //add
  //_block->SetType(_blockType);
  _map->AddBlock(_x, _z, _blockType);
}