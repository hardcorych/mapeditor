#pragma once

#include <osgViewer/Viewer>
#include <qobject.h>

class Viewer : public osgViewer::Viewer,
  public QObject
{
public:
  Viewer() = default;
  ~Viewer();

  public slots:
  void onQuitViewer();		//выход из потока
};

