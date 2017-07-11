#pragma once

#include <qevent.h>

#include <MapEditor.h>

class AddEvent : public QEvent
{
public:
  AddEvent() = delete;
  AddEvent(osg::ref_ptr<Map> map, 
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

public:
  inline osg::ref_ptr<Map> GetMap();
  inline int GetX();
  inline int GetZ();
  inline const BlockType& GetBlockType();

private:
  osg::ref_ptr<Map> _map;
  int _x;
  int _z;
  BlockType _blockType;
};

inline osg::ref_ptr<Map> AddEvent::GetMap()
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