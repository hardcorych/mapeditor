#pragma once

#include <qevent.h>

#include <MapEditor.h>

class ReplaceEvent : public QEvent
{
public:
  ReplaceEvent() = delete;
  ReplaceEvent(osg::ref_ptr<Map> map,
               osg::ref_ptr<Block> block,
               const BlockType& blockType) : 
    QEvent((Type)MapEditor::CustomEvent::REPLACE),
    _map(map),
    _block(block),
    _blockType(blockType)
  {
  }

public:
  inline osg::ref_ptr<Map> GetMap();
  inline osg::ref_ptr<Block> GetBlock();
  inline const BlockType& GetBlockType();

private:
  osg::ref_ptr<Map> _map;
  osg::ref_ptr<Block> _block;
  BlockType _blockType;
};

inline osg::ref_ptr<Map> ReplaceEvent::GetMap()
{
  return _map;
}

inline osg::ref_ptr<Block> ReplaceEvent::GetBlock()
{
  return _block;
}

inline const BlockType& ReplaceEvent::GetBlockType()
{
  return _blockType;
}