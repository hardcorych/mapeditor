#pragma once

#include <Commands.h>

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