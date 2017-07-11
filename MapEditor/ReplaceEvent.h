#pragma once

#include <qevent.h>

#include <MapEditor.h>

class ReplaceEvent : public QEvent
{
public:
  ReplaceEvent() = delete;
  ReplaceEvent(Map& map,
               Block& block,
               const BlockType& blockType) : 
    QEvent((Type)MapEditor::CustomEvent::REPLACE),
    _map(map),
    _block(block),
    _blockType(blockType)
  {
  }

public:
  inline Map& GetMap();
  inline Block& GetBlock();
  inline const BlockType& GetBlockType();

private:
  Map& _map;
  Block& _block;
  BlockType _blockType;
};

inline Map& ReplaceEvent::GetMap()
{
  return _map;
}

inline Block& ReplaceEvent::GetBlock()
{
  return _block;
}

inline const BlockType& ReplaceEvent::GetBlockType()
{
  return _blockType;
}