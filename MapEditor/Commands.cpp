#include <Commands.h>

AddCommand::AddCommand(Block* block, QUndoCommand* parent) :
QUndoCommand(parent)
{

}

AddCommand::~AddCommand()
{

}

void AddCommand::undo()
{
	//remove
}

void AddCommand::redo()
{
	//add
}

DeleteCommand::DeleteCommand(Block* block, QUndoCommand* parent) :
QUndoCommand(parent)
{

}

DeleteCommand::~DeleteCommand()
{

}

void DeleteCommand::undo()
{
	//add
}

void DeleteCommand::redo()
{
	//remove
}