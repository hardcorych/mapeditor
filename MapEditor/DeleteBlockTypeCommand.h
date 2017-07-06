#pragma once

#include <qundostack.h>

#include <MapEditor.h>

class DeleteBlockTypeCommand : public QUndoCommand
{
public:
  DeleteBlockTypeCommand(QButtonGroup* btnGroup, 
                         const BlockType& blockType,
                         MapEditor* mapEditor, 
                         QUndoCommand* parent = 0);
  ~DeleteBlockTypeCommand();

  void undo() override;
  void redo() override;

private:
  BlockType _blockType;
  MapEditor* _mapEditor;
  QRadioButton* _button;
  int _buttonId;
  QButtonGroup* _btnGroup;
  int _row;
  int _col;
};