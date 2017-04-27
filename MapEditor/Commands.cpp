#pragma once

#include <Commands.h>

//AddCommand

AddCommand::AddCommand(Block* block, TexType type, FillType fType, QUndoCommand* parent) :
QUndoCommand(parent)
{
	_block = block;
	_type = type;
	_fType = fType;
}

AddCommand::~AddCommand()
{
}

void AddCommand::undo()
{
	//remove
	_block->SetBlock(TexType::EMPTY, FillType::FULL);
}

void AddCommand::redo()
{
	//add
	_block->SetBlock(_type, _fType);
}

//ReplaceCommand

ReplaceCommand::ReplaceCommand(Block* block, TexType type, FillType fType, QUndoCommand* parent) :
QUndoCommand(parent)
{
	_block = block;
	_type = type;
	_fType = fType;
	_typeOld = block->GetType();
	_fTypeOld = block->GetFillType();
}

ReplaceCommand::~ReplaceCommand()
{
}

void ReplaceCommand::undo()
{
	//replace with old
	_block->SetBlock(_typeOld, _fTypeOld);
}

void ReplaceCommand::redo()
{
	//replace with new
	_block->SetBlock(_type, _fType);
}

//RemoveCommand

RemoveCommand::RemoveCommand(Block* block, QUndoCommand* parent) :
QUndoCommand(parent)
{
	_block = block;
	_type = _block->GetType();
	_fType = _block->GetFillType();
}

RemoveCommand::~RemoveCommand()
{
}

void RemoveCommand::undo()
{
	//add
	_block->SetBlock(_type, _fType);
}

void RemoveCommand::redo()
{
	//remove
	_block->SetBlock(TexType::EMPTY, FillType::FULL);
}

//ChangeSizeCommand

ChangeSizeCommand::ChangeSizeCommand(osg::ref_ptr<Map> map, int mapSizeX, int mapSizeZ, QUndoCommand* parent) :
QUndoCommand(parent)
{
	_map = map;
	_mapSizeX = mapSizeX;
	_mapSizeZ = mapSizeZ;
}

ChangeSizeCommand::~ChangeSizeCommand()
{
}

void ChangeSizeCommand::undo()
{
	//set old map
	//restoration of deleted blocks
}

void ChangeSizeCommand::redo()
{
	//set new map size
	deletedBlocks = _map->Resize(_mapSizeX, _mapSizeZ);
}