#pragma once

#include <qevent.h>

#include "MapEditor.h"

class RemoveEvent : public QEvent
{
public:
  RemoveEvent() = delete;
  RemoveEvent(const RemoveEvent&) = delete;
  RemoveEvent(Map& map,
              int x,
              int z,
              const BlockType& blockType) : 
    QEvent((Type)MapEditor::CustomEvent::REMOVE),
    _map(map),
    _x(x),
    _z(z),
    _blockType(blockType)
  {
  }
  ~RemoveEvent() = default;

  RemoveEvent& operator=(const RemoveEvent&) = delete;

public:
  inline Map& GetMap();
  inline int GetX();
  inline int GetZ();
  inline const BlockType& GetBlockType();

private:
  Map& _map;
  int _x;
  int _z;
  BlockType _blockType;
};

inline Map& RemoveEvent::GetMap()
{
  return _map;
}

inline int RemoveEvent::GetX()
{
  return _x;
}

inline int RemoveEvent::GetZ()
{
  return _z;
}

inline const BlockType& RemoveEvent::GetBlockType()
{
  return _blockType;
}