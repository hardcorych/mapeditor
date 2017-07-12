#pragma once

#include <qundostack.h>

#include "BlockType.h"

class Map;

class AddCommand : public QUndoCommand	//add block on map
{
public:
  AddCommand() = delete;
  AddCommand(const AddCommand&) = delete;
  AddCommand(Map& map, 
             int x,
             int z,
             const BlockType& blockType,
             QUndoCommand* parent = nullptr);
  ~AddCommand() = default;

  AddCommand& operator=(const AddCommand&) = delete;

  void undo() override;
  void redo() override;

private:
  Map& _map;
  int _x;
  int _z;
  BlockType _blockType;
};