#pragma once

#include <qevent.h>

#include <MapEditor.h>

class RedoEvent : public QEvent
{
public:
  RedoEvent() : QEvent((Type)MapEditor::CustomEvent::REDO_EVENT)
  {
  }
};