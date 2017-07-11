#pragma once

#include <qevent.h>

#include <MapEditor.h>

class RemoveEvent : public QEvent
{
public:
  RemoveEvent() = delete;
  RemoveEvent(osg::ref_ptr<Map> map,
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

inline osg::ref_ptr<Map> RemoveEvent::GetMap()
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