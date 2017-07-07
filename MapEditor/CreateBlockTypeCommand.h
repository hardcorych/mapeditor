#pragma once

#include <qundostack.h>

#include <MapEditor.h>

class CreateBlockTypeCommand : public QUndoCommand
{
public:
  CreateBlockTypeCommand(const BlockType& blockType, 
                         MapEditor& mapEditor, 
                         QUndoCommand* parent = 0);
  ~CreateBlockTypeCommand();

  void undo() override;
  void redo() override;

private:
  BlockType _blockType;
  MapEditor& _mapEditor;
  unsigned int _blockTypeId;
  //QRadioButton* _button;
  //QButtonGroup* _btnGroup;
  //int _row;
  //int _col;
};