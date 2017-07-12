#pragma once

#include <qevent.h>

#include "MapEditor.h"

class UndoEvent : public QEvent
{
public:
  UndoEvent() : QEvent((Type)MapEditor::CustomEvent::UNDO)
  {
  }
  UndoEvent(const UndoEvent&) = delete;
  ~UndoEvent() = default;

  UndoEvent& operator=(const UndoEvent& other) = delete;
};