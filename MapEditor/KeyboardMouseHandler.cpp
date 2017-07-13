#pragma once
#include <KeyboardMouseHandler.h>

#include <osgUtil/PolytopeIntersector>
#include <osgViewer/Viewer>

#include <AddEvent.h>
#include <Block.h>
#include <Map.h>
#include <RedoEvent.h>
#include <RemoveEvent.h>
#include <ReplaceEvent.h>
#include <UndoEvent.h>

KeyboardMouseHandler::KeyboardMouseHandler(MapEditor& mapEditor) :
  _mouseX(0),
  _mouseY(0),
  _mapEditor(mapEditor)
{
}

bool KeyboardMouseHandler::handle(const osgGA::GUIEventAdapter& ea, 
                                  osgGA::GUIActionAdapter& aa)
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

      osg::ref_ptr<Map> map = nullptr;
      osg::ref_ptr<Block> block = nullptr;

      findBlockAndMap(_mouseX, _mouseY, viewer, map, block);

      switch (ea.getButton())
      {
      case(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) :
      {
        //adding/changing the block
        if (map.valid() && block.valid())
        {
          BlockType blockType = _mapEditor.GetSelectedBlockType();

          if (block->GetType().isNotBorderType() && !blockType.isNoData())
          {
            if (!block->GetType().isNotEmptyType())
            {
              AddEvent* addEvent = 
                new AddEvent(*map, block->GetX(), block->GetZ(), blockType);
              QCoreApplication::postEvent(&_mapEditor, addEvent);
            }
            else if (block->GetType() != blockType)
            {
              ReplaceEvent* replaceEvent =
                new ReplaceEvent(*map, *block, blockType);
              QCoreApplication::postEvent(&_mapEditor, replaceEvent);
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
          if (blockType.isNotBorderType() && blockType.isNotEmptyType())
          {
            RemoveEvent* removeEvent =
              new RemoveEvent(*map, block->GetX(), block->GetZ(), blockType);
            QCoreApplication::postEvent(&_mapEditor, removeEvent);
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
      QCoreApplication::postEvent(&_mapEditor, new UndoEvent);
      return true;
    }
    else if (ea.getUnmodifiedKey() == osgGA::GUIEventAdapter::KEY_Y &&
             (ea.getModKeyMask() == osgGA::GUIEventAdapter::MODKEY_LEFT_CTRL ||
             ea.getModKeyMask() == osgGA::GUIEventAdapter::MODKEY_RIGHT_CTRL))
    {
      QCoreApplication::postEvent(&_mapEditor, new RedoEvent);
      return true;
    }

    return false;
  }
  default:
    return false;
  }
}

void KeyboardMouseHandler::findBlockAndMap(double x, 
                                           double y,
                                           osgViewer::Viewer* viewer, 
                                           osg::ref_ptr<Map>& mapOutput,
                                           osg::ref_ptr<Block>& blockOutput)
{
  if (viewer->getSceneData() == nullptr) return;	                  

  osg::ref_ptr<osgUtil::LineSegmentIntersector> picker = 
    new osgUtil::LineSegmentIntersector(osgUtil::Intersector::PROJECTION, 
                                        x,
                                        y);

  osgUtil::IntersectionVisitor iv(picker);

  viewer->getCamera()->accept(iv);

  if (picker->containsIntersections())
  {
    osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;
    unsigned int idx = nodePath.size();

    //find block and map
    while ((idx--) && (blockOutput == nullptr || mapOutput == nullptr))
    {
      if (blockOutput == nullptr)
        blockOutput = dynamic_cast<Block*>(nodePath[idx]);
      if (mapOutput == nullptr)
        mapOutput = dynamic_cast<Map*>(nodePath[idx]);
    }
  }
}