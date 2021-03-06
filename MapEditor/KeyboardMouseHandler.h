#pragma once

#include <osgGA/GUIEventHandler>

class Block;
class Map;
class MapEditor;

namespace osgViewer
{
  class Viewer;
}

///���������� ����� �� ����� ������ ����
///�������� ����� �� ������ ������ ����
class KeyboardMouseHandler : public osgGA::GUIEventHandler
{
public:
  KeyboardMouseHandler() = delete;
  KeyboardMouseHandler(const KeyboardMouseHandler&) = delete;
  KeyboardMouseHandler(MapEditor& mapEditor);

protected:
  ~KeyboardMouseHandler() = default; 

public:
  virtual bool handle(const osgGA::GUIEventAdapter& ea,
                      osgGA::GUIActionAdapter& aa);

private:
  void findBlockAndMap(double x,
                       double y,
                       osgViewer::Viewer* viewer,
                       osg::ref_ptr<Map>& mapOutput,
                       osg::ref_ptr<Block>& blockOutput);

private:
  double _mouseX;
  double _mouseY;   

  MapEditor& _mapEditor;
};

