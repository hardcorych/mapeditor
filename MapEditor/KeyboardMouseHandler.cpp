#include "KeyboardMouseHandler.h"

#include <algorithm>
#include <memory>

KeyboardMouseHandler::KeyboardMouseHandler() :
_mouseX(0), _mouseY(0)
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
      switch (ea.getButton())
      {
      case(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) :
      {
        //adding/changing the block
        //screen coordinates normalization for PolytopeIntersector
        _mouseX = ea.getXnormalized();	
        _mouseY = ea.getYnormalized();

        std::pair<bool, osg::ref_ptr<Block>> validBlock = findBlockAndMap(_mouseX, _mouseY, viewer);
        bool isValid = std::get<0>(validBlock);
        if (isValid)
        {
          osg::ref_ptr<Block> block = std::get<1>(validBlock);
          //!!!!!!!!!!!!!!!!
          if (block->GetType().GetTypeName() != "BORDER")
          {
            if (block->GetType().GetTypeName() == "EMPTY")
            {
              emit AddableBlock(block, _blockType);
            }
            else if (block->GetType() != _blockType)
            {
              emit ReplaceableBlock(block, _blockType);
            }
          }
          return true;	//TRUE to process an event
        }
        return false;
      }
      case(osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) :
      {
        //removing the block
        //screen coordinates normalization for PolytopeIntersector
        _mouseX = ea.getXnormalized();
        _mouseY = ea.getYnormalized();

        std::pair<bool, osg::ref_ptr<Block>> validBlock =
          findBlockAndMap(_mouseX, _mouseY, viewer);
        bool isValid = std::get<0>(validBlock);
        if (isValid)
        {
          osg::ref_ptr<Block> block = std::get<1>(validBlock);
          BlockType blockType = block->GetType();
          if (blockType.GetTypeName() != "BORDER" && 
            blockType.GetTypeName() != "EMPTY")
          {
            //emit to delete command
            emit RemovableBlock(block);
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
      emit Undo();
      return true;
    }
    else if (ea.getUnmodifiedKey() == osgGA::GUIEventAdapter::KEY_Y &&
      (ea.getModKeyMask() == osgGA::GUIEventAdapter::MODKEY_LEFT_CTRL ||
      ea.getModKeyMask() == osgGA::GUIEventAdapter::MODKEY_RIGHT_CTRL))
    {
      emit Redo();
      return true;
    }

    return false;
  }
  default:
    return false;
  }
}

std::pair<bool, osg::ref_ptr<Block>> 
KeyboardMouseHandler::findBlockAndMap(const double x, const double y,
                                      osgViewer::Viewer* viewer)
{
  if (!viewer->getSceneData())
    return std::make_pair(false, nullptr);	//nothing to pick

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
  return std::make_pair((selectedBlock.valid() && selectedMap.valid()), block);
}

void KeyboardMouseHandler::ReceiveBlock(BlockType blockType)
{
  _blockType = blockType;
}