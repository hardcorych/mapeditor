#include "Viewer.h"

Viewer::~Viewer()
{
}

void Viewer::onQuitViewer()
{
  setDone(true);
}
