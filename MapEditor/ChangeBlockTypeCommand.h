#pragma once

#include <qundostack.h>

#include <MapEditor.h>

class ChangeBlockTypeCommand : public QUndoCommand
{
public:
  ChangeBlockTypeCommand(MapEditor::BlockTypes& blockTypes,
                         const BlockType& blockType, 
                         const BlockType& blockTypeNew,
                         MapEditor& mapEditor, 
                         QUndoCommand* parent = nullptr);
  ~ChangeBlockTypeCommand();

  void undo() override;
  void redo() override;

private:
  MapEditor::BlockTypes& _blockTypes;
  BlockType _blockType;
  BlockType _blockTypeNew;
  MapEditor& _mapEditor;
};