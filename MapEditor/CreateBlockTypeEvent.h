#pragma once

#include <qevent.h>

#include <MapEditor.h>

class CreateBlockTypeEvent : public QEvent
{
public:
  CreateBlockTypeEvent() = delete;
  CreateBlockTypeEvent(const BlockType& blockType) :
    QEvent((Type)MapEditor::CustomEvent::CREATE_BLOCKTYPE),
    _blockType(blockType)
  {
  }

public:
  inline const BlockType& GetBlockType();

private:
  BlockType _blockType;
};

inline const BlockType& CreateBlockTypeEvent::GetBlockType()
{
  return _blockType;
}