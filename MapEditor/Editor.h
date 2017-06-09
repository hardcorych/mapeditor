#pragma once

#include <qaction.h>
#include <qundostack.h>

//abstract class
class Editor
{
public:
  Editor() = default;
  virtual ~Editor() = default;

protected:
  QUndoStack* _undoStack;
  QAction* _undoAct;
  QAction* _redoAct;
};