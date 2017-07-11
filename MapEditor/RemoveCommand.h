#pragma once

#include <qundostack.h>

class BlockType;
class Map;

class RemoveCommand : public QUndoCommand	//remove block from map
{
public:
  RemoveCommand(Map& map,
                int x, 
                int z,
                const BlockType& blockType, 
                QUndoCommand* parent = nullptr);
  ~RemoveCommand();

  void undo() override;
  void redo() override;

private:
  Map& _map;
  int _x;
  int _z;
  BlockType _blockType;
};