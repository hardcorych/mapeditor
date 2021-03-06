#pragma once

#include <qevent.h>

#include <MapEditor.h>

class RedoEvent : public QEvent
{
public:
  RedoEvent() : QEvent((Type)MapEditor::CustomEvent::REDO)
  {
  }
  RedoEvent(const RedoEvent&) = delete;
  ~RedoEvent() = default;

  RedoEvent& operator=(const RedoEvent&) = delete;
};