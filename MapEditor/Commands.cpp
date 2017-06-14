#pragma once

#include <Commands.h>

//AddCommand

AddCommand::AddCommand(osg::ref_ptr<Map> map, osg::ref_ptr<Block> block, std::string type,
  FillType fType, QUndoCommand* parent) :
QUndoCommand(parent)
{
  _block = block;
  _type = type;
  _texPath = map->GetTexPath(type);
  _fType = fType;
}

AddCommand::~AddCommand()
{
}

void AddCommand::undo()
{
  //remove
  _block->SetType("EMPTY", "", FillType::FULL);
}

void AddCommand::redo()
{
  //add
  _block->SetType(_type, _texPath, _fType);
}

//ReplaceCommand

ReplaceCommand::ReplaceCommand(osg::ref_ptr<Map> map, osg::ref_ptr<Block> block,
  std::string type, FillType fType, QUndoCommand* parent) :
QUndoCommand(parent)
{
  _block = block;
  _type = type;
  _fType = fType;
  _texPath = map->GetTexPath(type);
  _texPathOld = block->GetTexPath();
  _typeOld = block->GetType();
  _fTypeOld = block->GetFillType();
}

ReplaceCommand::~ReplaceCommand()
{
}

void ReplaceCommand::undo()
{
  //replace with old
  _block->SetType(_typeOld, _texPathOld, _fTypeOld);
}

void ReplaceCommand::redo()
{
  //replace with new
  _block->SetType(_type, _texPath, _fType);
}

//RemoveCommand

RemoveCommand::RemoveCommand(osg::ref_ptr<Block> block, QUndoCommand* parent) :
QUndoCommand(parent)
{
  _block = block;
  _type = _block->GetType();
  _texPath = _block->GetTexPath();
  _fType = _block->GetFillType();
}

RemoveCommand::~RemoveCommand()
{
}

void RemoveCommand::undo()
{
  //add
  _block->SetType(_type, _texPath, _fType);
}

void RemoveCommand::redo()
{
  //remove
  _block->SetType("EMPTY", "", FillType::FULL);
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