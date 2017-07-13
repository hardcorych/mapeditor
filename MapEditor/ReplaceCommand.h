#pragma once

#include <qundostack.h>

#include <BlockType.h>

class Block;
class Map;

///replace existing block on map
class ReplaceCommand : public QUndoCommand	
{
public:
  ReplaceCommand() = delete;
  ReplaceCommand(const ReplaceCommand&) = delete;
  ReplaceCommand(Map& map,
                 const Block& block,
                 const BlockType& blockType,
                 QUndoCommand* parent = 0);
  ~ReplaceCommand() = default;

  ReplaceCommand& operator=(const ReplaceCommand&) = delete;

  void undo() override;
  void redo() override;

private:
  Map& _map;
  BlockType _blockType;
  BlockType _blockTypeOld;
  int _x;
  int _z;
};