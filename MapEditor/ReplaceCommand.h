#pragma once

#include <qundostack.h>

#include <Map.h>

class ReplaceCommand : public QUndoCommand	//replace existing block on map
{
public:
  ReplaceCommand(Map& map,
                 const Block& block,
                 const BlockType& blockType,
                 QUndoCommand* parent = 0);
  ~ReplaceCommand();

  void undo() override;
  void redo() override;

private:
  Map& _map;
  BlockType _blockType;
  BlockType _blockTypeOld;
  int _x;
  int _z;
};