#pragma once

#include <QtWidgets/QApplication>

#include "MapEditor.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MapEditor w;

  QObject::connect(&w, &MapEditor::QuitAppToMain, &a, &QApplication::quit);

  w.show();
  return a.exec();
}
