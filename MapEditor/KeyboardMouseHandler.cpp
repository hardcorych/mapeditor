#include "KeyboardMouseHandler.h"

#include <algorithm>
#include <memory>

KeyboardMouseHandler::KeyboardMouseHandler(MapEditor* mapEditor) :
_mouseX(0), _mouseY(0),
_mapEditor(mapEditor)
{
}

KeyboardMouseHandler::~KeyboardMouseHandler()
{
}

bool KeyboardMouseHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
  osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);

  if (!viewer) return false;

  switch (ea.getEventType())
  {
  case(osgGA::GUIEventAdapter::PUSH) :
  case(osgGA::GUIEventAdapter::MOVE) :
  {
    _mouseX = ea.getX();
    _mouseY = ea.getY();

    return false;
  }
  case(osgGA::GUIEventAdapter::RELEASE) :
  {
    if (_mouseX == ea.getX() && _mouseY == ea.getY())
    {
      //screen coordinates normalization for PolytopeIntersector
      _mouseX = ea.getXnormalized();
      _mouseY = ea.getYnormalized();

      std::pair<osg::ref_ptr<Map>, osg::ref_ptr<Block>> blockAndMap =
        findBlockAndMap(_mouseX, _mouseY, viewer);

      osg::ref_ptr<Map> map = std::get<0>(blockAndMap);
      osg::ref_ptr<Block> block = std::get<1>(blockAndMap);
      switch (ea.getButton())
      {
      case(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) :
      {
        //adding/changing the block
        if (map.valid() && block.valid())
        {
          _blockType = _mapEditor->GetSelectedBlockType();

          if (block->GetType().GetTypeName() != "BORDER" &&
            !_blockType.isEmpty())
          {
            if (block->GetType().GetTypeName() == "EMPTY")
            {
              _mapEditor->AddBlock(map, block->GetX(), block->GetZ(),
                _blockType);
            }
            else if (block->GetType() != _blockType)
            {
              _mapEditor->ReplaceBlock(map, block, _blockType);
            }
          }
          return true;	//TRUE to process an event
        }
        return false;
      }
      case(osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) :
      {
        //removing the block
        if (map.valid() && block.valid())
        {
          BlockType blockType = block->GetType();
          if (blockType.GetTypeName() != "BORDER" && 
            blockType.GetTypeName() != "EMPTY")
          {
            //emit to delete command
            _mapEditor->RemoveBlock(map, block->GetX(),
              block->GetZ(), blockType);
          }
          return true;	//TRUE to process an event
        }
        return false;
      }
      }
    }
  }
  case (osgGA::GUIEventAdapter::KEYDOWN) :
  {
    //undo/redo actions

    if (ea.getUnmodifiedKey() == osgGA::GUIEventAdapter::KEY_Z &&
      (ea.getModKeyMask() == osgGA::GUIEventAdapter::MODKEY_LEFT_CTRL ||
      ea.getModKeyMask() == osgGA::GUIEventAdapter::MODKEY_RIGHT_CTRL))
    {
      _mapEditor->Undo();
      return true;
    }
    else if (ea.getUnmodifiedKey() == osgGA::GUIEventAdapter::KEY_Y &&
      (ea.getModKeyMask() == osgGA::GUIEventAdapter::MODKEY_LEFT_CTRL ||
      ea.getModKeyMask() == osgGA::GUIEventAdapter::MODKEY_RIGHT_CTRL))
    {
      _mapEditor->Redo();
      return true;
    }

    return false;
  }
  default:
    return false;
  }
}

std::pair<osg::ref_ptr<Map>, osg::ref_ptr<Block>> 
KeyboardMouseHandler::findBlockAndMap(const double x, const double y,
                                      osgViewer::Viewer* viewer)
{
  //if (!viewer->getSceneData())
    //return std::make_pair(false, nullptr);	//nothing to pick

  osg::ref_ptr<osgUtil::LineSegmentIntersector> picker = 
    new osgUtil::LineSegmentIntersector(
    osgUtil::Intersector::PROJECTION, x, y);

  osgUtil::IntersectionVisitor iv(picker);

  viewer->getCamera()->accept(iv);

  osg::ref_ptr<osg::Node> selectedBlock = nullptr;
  osg::ref_ptr<osg::Node> selectedMap = nullptr;

  //get block and map
  osg::ref_ptr<Map> map = nullptr;
  osg::ref_ptr<Block> block = nullptr;

  if (picker->containsIntersections())
  {
    osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;
    unsigned int idx = nodePath.size();

    //find block and map
    while ((idx--) && (block == nullptr || map == nullptr))
    {
      if (block == nullptr)
        block = dynamic_cast<Block*>(nodePath[idx]);
      if (map == nullptr)
        map = dynamic_cast<Map*>(nodePath[idx]);
    }

    selectedBlock = block;
    selectedMap = map;
  }
  //!!!!!!!!!!!!!
  //return std::make_pair((selectedBlock.valid() && selectedMap.valid()), block);
  return std::make_pair(map, block);
}