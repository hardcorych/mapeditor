#pragma once

#include <qevent.h>

#include "MapEditor.h"

class DeleteBlockTypeEvent : public QEvent
{
public:
  DeleteBlockTypeEvent() = delete;
  DeleteBlockTypeEvent(const DeleteBlockTypeEvent&) = delete;
  DeleteBlockTypeEvent(int blockTypeId) :
    QEvent((Type)MapEditor::CustomEvent::DELETE_BLOCKTYPE),
    _blockTypeId(blockTypeId)
  {
  }
  ~DeleteBlockTypeEvent() = default;

  DeleteBlockTypeEvent& operator=(const DeleteBlockTypeEvent&) = delete;

public:
  inline int GetBlockTypeId();

private:
  int _blockTypeId;
};

inline int DeleteBlockTypeEvent::GetBlockTypeId()
{
  return _blockTypeId;
}