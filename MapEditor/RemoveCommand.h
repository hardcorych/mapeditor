#pragma once

#include <qundostack.h>

#include "BlockType.h"

class Map;

class RemoveCommand : public QUndoCommand	//remove block from map
{
public:
  RemoveCommand() = delete;
  RemoveCommand(const RemoveCommand&) = delete;
  RemoveCommand(Map& map,
                int x, 
                int z,
                const BlockType& blockType, 
                QUndoCommand* parent = nullptr);
  ~RemoveCommand() = default;

  RemoveCommand& operator=(const RemoveCommand&) = delete;

  void undo() override;
  void redo() override;

private:
  Map& _map;
  int _x;
  int _z;
  BlockType _blockType;
};