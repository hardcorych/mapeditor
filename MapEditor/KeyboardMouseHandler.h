#pragma once

#include <memory>

#include <osgGA/GUIEventHandler>
#include <osgUtil/PolytopeIntersector>
#include <osgViewer/Viewer>

#include <qobject.h>

#include <Block.h>
#include <Map.h>
#include <MapEditor.h>

class KeyboardMouseHandler : public osgGA::GUIEventHandler
{
public:
  KeyboardMouseHandler(MapEditor* mapEditor);
  ~KeyboardMouseHandler();

  //добавление блока по левой кнопке мыши
  //удаление блока по правой кнопке мыши
  virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

protected:
  double _mouseX, _mouseY;	//mouse coords

  BlockType _blockType;   //!!!

  //std::shared_ptr<MapEditor> _mapEditor;
  MapEditor* _mapEditor;

  std::pair<osg::ref_ptr<Map>, osg::ref_ptr<Block>> 
    findBlockAndMap(const double x, const double y, osgViewer::Viewer* viewer);
};

