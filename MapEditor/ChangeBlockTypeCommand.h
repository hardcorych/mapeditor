#pragma once

#include <qundostack.h>

#include <MapEditor.h>

class BlockType;

///change blocktype in block editor
class ChangeBlockTypeCommand : public QUndoCommand
{
public:
  ChangeBlockTypeCommand() = delete;
  ChangeBlockTypeCommand(const ChangeBlockTypeCommand&) = delete;
  ChangeBlockTypeCommand(MapEditor::BlockTypes& blockTypes,
                         const BlockType& blockType, 
                         const BlockType& blockTypeNew,
                         MapEditor& mapEditor, 
                         QUndoCommand* parent = nullptr);
  ~ChangeBlockTypeCommand() = default;

  ChangeBlockTypeCommand& operator=(const ChangeBlockTypeCommand&) = delete;

  void undo() override;
  void redo() override;

private:
  MapEditor::BlockTypes& _blockTypes;
  BlockType _blockType;
  BlockType _blockTypeNew;
  MapEditor& _mapEditor;
};