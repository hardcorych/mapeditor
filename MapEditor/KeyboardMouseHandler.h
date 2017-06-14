#pragma once
#include <osgGA/GUIEventHandler>
#include <osgUtil/PolytopeIntersector>
#include <osgViewer/Viewer>

#include <qobject.h>

#include <Block.h>
#include <Map.h>

class KeyboardMouseHandler : public QObject, public osgGA::GUIEventHandler
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

  //TexType _type;
  std::string _type;
  FillType _fType;

  std::pair<bool, osg::ref_ptr<Block>> findBlockAndMap(const double x, const double y, osgViewer::Viewer* viewer);

signals:
  void AddableBlock(osg::ref_ptr<Block> block, std::string type, FillType fType);
  void RemovableBlock(osg::ref_ptr<Block> block);
  void ReplaceableBlock(osg::ref_ptr<Block> block, std::string type, FillType fType);
  void Undo();
  void Redo();

  public slots:
  void ReceiveBlock(std::string type, FillType fillType);
};

