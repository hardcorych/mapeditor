#pragma once

#include <qundostack.h>

#include <MapEditor.h>

class ChangeBlockTypeCommand : public QUndoCommand
{
public:
  ChangeBlockTypeCommand(QAbstractButton* button,
                         BlockType blockType, 
                         BlockType blockTypeNew,
                         MapEditor* mapEditor, 
                         QUndoCommand* parent = 0);
  ~ChangeBlockTypeCommand();

  void undo() override;
  void redo() override;

private:
  //BlockType& _blockTypeRef;
  BlockType _blockType;
  BlockType _blockTypeNew;
  QAbstractButton* _button;
  MapEditor* _mapEditor;
};