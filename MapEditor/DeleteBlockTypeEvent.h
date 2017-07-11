#pragma once

#include <qevent.h>

#include <MapEditor.h>

class DeleteBlockTypeEvent : public QEvent
{
public:
  DeleteBlockTypeEvent() = delete;
  DeleteBlockTypeEvent(int blockTypeId) :
    QEvent((Type)MapEditor::CustomEvent::DELETE_BLOCKTYPE),
    _blockTypeId(blockTypeId)
  {
  }

public:
  inline int GetBlockTypeId();

private:
  int _blockTypeId;
};

inline int DeleteBlockTypeEvent::GetBlockTypeId()
{
  return _blockTypeId;
}