#pragma once

#include <qevent.h>

#include <MapEditor.h>

///event of replacing a block on map
class ReplaceEvent : public QEvent
{
public:
  ReplaceEvent() = delete;
  ReplaceEvent(const ReplaceEvent&) = delete;
  ReplaceEvent(Map& map,
               Block& block,
               const BlockType& blockType) : 
    QEvent((Type)MapEditor::CustomEvent::REPLACE),
    _map(map),
    _block(block),
    _blockType(blockType)
  {
  }
  ~ReplaceEvent() = default;

  ReplaceEvent& operator=(const ReplaceEvent& other) = delete;

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