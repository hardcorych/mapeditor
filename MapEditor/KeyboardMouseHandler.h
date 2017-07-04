#pragma once

#include <memory>

#include <osgGA/GUIEventHandler>
#include <osgUtil/PolytopeIntersector>
#include <osgViewer/Viewer>

#include <qobject.h>

#include <Block.h>
#include <Map.h>
#include <MapEditor.h>

class KeyboardMouseHandler : public QObject, public osgGA::GUIEventHandler
//class KeyboardMouseHandler : public osgGA::GUIEventHandler
{
  Q_OBJECT
public:
  KeyboardMouseHandler();
  ~KeyboardMouseHandler();

  //добавление блока по левой кнопке мыши
  //удаление блока по правой кнопке мыши
  virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

protected:
  double _mouseX, _mouseY;	//mouse coords

  BlockType _blockType;

  std::unique_ptr<MapEditor> _mapEditor;

  std::pair<osg::ref_ptr<Map>, osg::ref_ptr<Block>> 
    findBlockAndMap(const double x, const double y, osgViewer::Viewer* viewer);

signals:
  void RemoveBlock(osg::ref_ptr<Map> map, int x, int z, BlockType blockType);
  //void RemovableBlock(osg::ref_ptr<Block> block);
  //void AddableBlock(osg::ref_ptr<Block> block, BlockType blockType);
  void AddBlock(osg::ref_ptr<Map> map, int x, int z, BlockType blockType);
  //void ReplaceableBlock(osg::ref_ptr<Block> block, BlockType blockType);
  void ReplaceableBlock(osg::ref_ptr<Map> map,
    osg::ref_ptr<Block> block, BlockType blockType);

  void Undo();
  void Redo();

  public slots:
  void ReceiveBlock(BlockType blockType);
};

