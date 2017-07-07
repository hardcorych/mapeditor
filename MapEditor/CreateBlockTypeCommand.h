#pragma once

#include <qundostack.h>

#include <MapEditor.h>

class CreateBlockTypeCommand : public QUndoCommand
{
public:
  CreateBlockTypeCommand(const BlockType& blockType, 
                         MapEditor& mapEditor, 
                         QUndoCommand* parent = nullptr);
  ~CreateBlockTypeCommand();

  void undo() override;
  void redo() override;

private:
  BlockType _blockType;
  MapEditor& _mapEditor;
  int _blockTypeId;
};