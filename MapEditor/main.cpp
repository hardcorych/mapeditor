#include "MapEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MapEditor w;

  QObject::connect(&w, &MapEditor::QuitAppToMain, &a, &QApplication::quit);

  w.show();
  return a.exec();
}
