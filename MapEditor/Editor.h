#pragma once

#include <qaction.h>
#include <qundostack.h>

//абстрактный класс
class Editor
{
public:
  Editor();
  ~Editor();

protected:
  QUndoStack* _undoStack;
  QAction* _undoAct;
  QAction* _redoAct;
};

