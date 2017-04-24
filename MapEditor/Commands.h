// undo/redo commands
#pragma once
#include <qundostack.h>
#include <Block.h>

class AddCommand : public QUndoCommand	//команда добавления блока на карту
{
public:
	AddCommand(Block* block, TexType type, FillType fType, QUndoCommand* parent = 0);
	~AddCommand();

	void undo() override;
	void redo() override;

private:
	Block* _block = nullptr;
	TexType _type;
	FillType _fType;
};

class RemoveCommand : public QUndoCommand	//команда удаления блока с карты
{
public:
	RemoveCommand(Block* block, QUndoCommand* parent = 0);
	~RemoveCommand();

	void undo() override;
	void redo() override;

private:
	Block* _block = nullptr;
	TexType _type;
	FillType _fType;
};