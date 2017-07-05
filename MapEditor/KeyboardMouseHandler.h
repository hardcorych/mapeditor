#pragma once

#include <memory>

#include <osgGA/GUIEventHandler>
#include <osgUtil/PolytopeIntersector>
#include <osgViewer/Viewer>

#include <qobject.h>

#include <Block.h>
#include <Map.h>
#include <MapEditor.h>

///добавление блока по левой кнопке мыши
///удаление блока по правой кнопке мыши
class MapEditor;

class KeyboardMouseHandler : public osgGA::GUIEventHandler
{
public:
  //KeyboardMouseHandler() = delete;
  KeyboardMouseHandler(MapEditor* mapEditor);

protected:
  ~KeyboardMouseHandler(); 

public:
  virtual bool handle(const osgGA::GUIEventAdapter& ea,
    osgGA::GUIActionAdapter& aa);

private:
  void findBlockAndMap(const double x,
                       const double y,
                       osgViewer::Viewer* viewer,
                       osg::ref_ptr<Map>& mapOutput,
                       osg::ref_ptr<Block>& blockOutput);

private:
  double _mouseX;
  double _mouseY;

  BlockType _blockType;   

  MapEditor* _mapEditor;
};

