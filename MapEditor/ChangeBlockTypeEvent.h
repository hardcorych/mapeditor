#pragma once

#include <qevent.h>

#include <MapEditor.h>

class ChangeBlockTypeEvent : public QEvent
{
public:
  ChangeBlockTypeEvent() = delete;
  ChangeBlockTypeEvent(BlockType& blockType) :
    QEvent((Type)MapEditor::CustomEvent::CHANGE_BLOCKTYPE),
    _blockType(blockType)
  {
  }

public:
  inline BlockType& GetBlockType();

private:
  BlockType _blockType;
};

inline BlockType& ChangeBlockTypeEvent::GetBlockType()
{
  return _blockType;
}