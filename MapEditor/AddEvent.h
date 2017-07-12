#pragma once

#include <qevent.h>

#include "MapEditor.h"

class AddEvent : public QEvent
{
public:
  AddEvent() = delete;
  AddEvent(const AddEvent&) = delete;
  AddEvent(Map& map, 
           int x, 
           int z,
           const BlockType& blockType) : 
    QEvent((Type)MapEditor::CustomEvent::ADD),
    _map(map),
    _x(x),
    _z(z),
    _blockType(blockType)
  {
  }
  ~AddEvent() = default;

  AddEvent& operator=(const AddEvent&) = delete;

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

inline Map& AddEvent::GetMap()
{
  return _map;
}

inline int AddEvent::GetX()
{
  return _x;
}

inline int AddEvent::GetZ()
{
  return _z;
}

inline const BlockType& AddEvent::GetBlockType()
{
  return _blockType;
}