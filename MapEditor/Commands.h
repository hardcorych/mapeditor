// undo/redo commands

#include <qundostack.h>
#include <Block.h>

class AddCommand : public QUndoCommand
{
public:
	AddCommand(Block* block, QUndoCommand* parent);
	~AddCommand();

	void undo() override;
	void redo() override;

private:
};

class DeleteCommand : public QUndoCommand
{
public:
	DeleteCommand(Block* block, QUndoCommand* parent);
	~DeleteCommand();

	void undo() override;
	void redo() override;

private:
};