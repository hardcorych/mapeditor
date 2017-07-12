#pragma once

#include <qundostack.h>

#include "BlockType.h"
#include "MapEditor.h"

class DeleteBlockTypeCommand : public QUndoCommand
{
public:
  DeleteBlockTypeCommand() = delete;
  DeleteBlockTypeCommand(const DeleteBlockTypeCommand&) = delete;
  DeleteBlockTypeCommand(MapEditor::BlockTypes& blockTypes,
                         const BlockType& blockType,
                         int blockTypeId,
                         MapEditor& mapEditor, 
                         QUndoCommand* parent = nullptr);
  ~DeleteBlockTypeCommand() = default;

  DeleteBlockTypeCommand& operator=(const DeleteBlockTypeCommand&) = delete;

  void undo() override;
  void redo() override;

private:
  MapEditor::BlockTypes& _blockTypes;
  BlockType _blockType;
  MapEditor& _mapEditor;
  int _blockTypeId;
};