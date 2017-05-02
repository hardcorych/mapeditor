#include "KeyboardMouseHandler.h"
#include <algorithm>
#include <memory>

KeyboardMouseHandler::KeyboardMouseHandler():
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

	switch (ea.getEventType())	//получаем событие
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
				//добавление/изменение блока
				_mouseX = ea.getXnormalized();	//нормализация экранных координат для polytope intersector
				_mouseY = ea.getYnormalized();

				std::pair<bool, osg::ref_ptr<Block>> validBlock = findBlockAndMap(_mouseX, _mouseY, viewer);
				bool isValid = std::get<0>(validBlock);
				if (isValid)
				{
					osg::ref_ptr<Block> block = std::get<1>(validBlock);
					if (block->GetType() != TexType::BORDER)
					{
						//block->SetBlock(_type, _fType);		//add command
						//emit to add command
						if (block->GetType() == TexType::EMPTY)
						{
							emit AddableBlock(block, _type, _fType);
						}
						else if (!(block->GetType() == _type && block->GetFillType() == _fType))
						{
							emit ReplaceableBlock(block, _type, _fType);
						}
					}
					return true;	//true, чтобы обработать событие
				}
				return false;
			}
			case(osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) :
			{
				//удаление блока
				_mouseX = ea.getXnormalized();	//нормализация экранных координат для polytope intersector
				_mouseY = ea.getYnormalized();

				std::pair<bool, osg::ref_ptr<Block>> validBlock = findBlockAndMap(_mouseX, _mouseY, viewer);
				bool isValid = std::get<0>(validBlock);
				if (isValid)
				{
					osg::ref_ptr<Block> block = std::get<1>(validBlock);
					TexType blockType = block->GetType();
					if (blockType != TexType::BORDER &&
						blockType != TexType::EMPTY)
					{
						//block->SetBlock(TexType::EMPTY, FillType::FULL);		//delete command
						//emit to delete command
						emit RemovableBlock(block);
					}
					return true;	//true, чтобы обработать событие
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
	//default:
		//return false;
	}
}

std::pair<bool, osg::ref_ptr<Block>> KeyboardMouseHandler::findBlockAndMap(const double x, const double y, osgViewer::Viewer* viewer)
{
	if (!viewer->getSceneData())
		return std::make_pair(false, nullptr);	//nothing to pick

	osg::ref_ptr<osgUtil::LineSegmentIntersector> picker = new osgUtil::LineSegmentIntersector(
		osgUtil::Intersector::PROJECTION, x, y);

	osgUtil::IntersectionVisitor iv(picker);

	viewer->getCamera()->accept(iv);

	osg::ref_ptr<osg::Node> selectedBlock = nullptr;
	osg::ref_ptr<osg::Node> selectedMap = nullptr;

	//получить карту и блок
	//Map* map = nullptr;
	//Block* block = nullptr;
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

void KeyboardMouseHandler::ReceiveBlock(TexType type, FillType fillType)
{
	_type = type;
	_fType = fillType;
}