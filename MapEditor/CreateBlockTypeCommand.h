#pragma once

#include <qundostack.h>

#include "BlockType.h"
#include "MapEditor.h"

class CreateBlockTypeCommand : public QUndoCommand
{
public:
  CreateBlockTypeCommand() = delete;
  CreateBlockTypeCommand(const CreateBlockTypeCommand&) = delete;
  CreateBlockTypeCommand(MapEditor::BlockTypes& blockTypes,
                         const BlockType& blockType, 
                         MapEditor& mapEditor, 
                         QUndoCommand* parent = nullptr);
  ~CreateBlockTypeCommand() = default;

  CreateBlockTypeCommand& operator=(const CreateBlockTypeCommand&) = delete;

  void undo() override;
  void redo() override;

private:
  MapEditor::BlockTypes& _blockTypes;
  BlockType _blockType;
  MapEditor& _mapEditor;
  int _blockTypeId;
};