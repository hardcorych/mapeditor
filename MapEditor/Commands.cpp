#pragma once

#include <Commands.h>

//AddCommand

AddCommand::AddCommand(osg::ref_ptr<Block> block, 
  BlockType blockType, QUndoCommand* parent) :
QUndoCommand(parent),
_block(block),
_blockType(blockType)
{
}

AddCommand::~AddCommand()
{
}

void AddCommand::undo()
{
  //remove
  BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);
  _block->SetType(emptyBlock);
}

void AddCommand::redo()
{
  //add
  _block->SetType(_blockType);
}

//ReplaceCommand

ReplaceCommand::ReplaceCommand(osg::ref_ptr<Block> block,
  BlockType blockType, QUndoCommand* parent) :
QUndoCommand(parent),
_block(block),
_blockType(blockType)
{
  _blockTypeOld = block->GetType();
}

ReplaceCommand::~ReplaceCommand()
{
}

void ReplaceCommand::undo()
{
  //replace with old
  _block->SetType(_blockTypeOld);
}

void ReplaceCommand::redo()
{
  //replace with new
  _block->SetType(_blockType);
}

//RemoveCommand

RemoveCommand::RemoveCommand(osg::ref_ptr<Block> block, QUndoCommand* parent) :
QUndoCommand(parent),
_block(block)
{
  _blockType = block->GetType();
}

RemoveCommand::~RemoveCommand()
{
}

void RemoveCommand::undo()
{
  //add
  _block->SetType(_blockType);
}

void RemoveCommand::redo()
{
  //remove
  BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);
  _block->SetType(emptyBlock);
}

//ChangeSizeCommand

ChangeSizeCommand::ChangeSizeCommand(osg::ref_ptr<Map> map, 
  int mapSizeX, int mapSizeZ, QUndoCommand* parent) :
QUndoCommand(parent)
{
  _map = map;
  _mapSizeX = mapSizeX;
  _mapSizeZ = mapSizeZ;
  _mapSizeXOld = _map->GetSizeX() / 16;
  _mapSizeZOld = _map->GetSizeZ() / 16;
}

ChangeSizeCommand::~ChangeSizeCommand()
{
}

void ChangeSizeCommand::undo()
{
  //set old map
  deletedBlocks = _map->Resize(deletedBlocks, _mapSizeXOld, _mapSizeZOld);
}

void ChangeSizeCommand::redo()
{
  //set new map size
  deletedBlocks = _map->Resize(deletedBlocks, _mapSizeX, _mapSizeZ);
}

//CreateBlockTypeCommand
CreateBlockTypeCommand::CreateBlockTypeCommand(BlockType blockType,
  QUndoCommand* parent)
{

}

CreateBlockTypeCommand::~CreateBlockTypeCommand()
{
}

void CreateBlockTypeCommand::undo()
{

}

void CreateBlockTypeCommand::redo()
{

}