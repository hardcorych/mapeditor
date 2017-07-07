#pragma once

#include <qundostack.h>

#include <MapEditor.h>

class DeleteBlockTypeCommand : public QUndoCommand
{
public:
  DeleteBlockTypeCommand(const BlockType& blockType,
                         int blockTypeId,
                         MapEditor& mapEditor, 
                         QUndoCommand* parent = nullptr);
  ~DeleteBlockTypeCommand();

  void undo() override;
  void redo() override;

private:
  BlockType _blockType;
  MapEditor& _mapEditor;
  int _blockTypeId;
};