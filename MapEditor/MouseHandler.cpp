#include "MouseHandler.h"


MouseHandler::MouseHandler():
_mouseX(0), _mouseY(0)
{
}

MouseHandler::~MouseHandler()
{
}

bool MouseHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
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

				std::pair<bool, Block*> validBlock = findBlockAndMap(_mouseX, _mouseY, viewer);
				bool isValid = std::get<0>(validBlock);
				if (isValid)
				{
					osg::ref_ptr<Block> block = std::get<1>(validBlock);
					if (block->GetType() != TexType::BORDER &&
						block->GetType() == TexType::EMPTY &&
						!(block->GetType() == _type && block->GetFillType() == _fType))
					{
						//block->SetBlock(_type, _fType);		//add command
						//emit to add command
						emit AddableBlock(block, _type, _fType);
					}
					return true;	//true, чтобы обработать событие
				}
			}
			case(osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) :
			{
				//удаление блока
				_mouseX = ea.getXnormalized();	//нормализация экранных координат для polytope intersector
				_mouseY = ea.getYnormalized();

				std::pair<bool, Block*> validBlock = findBlockAndMap(_mouseX, _mouseY, viewer);
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
			}
			}
		}
	default:
		return false;
	}
	}
}

std::pair<bool, Block*> MouseHandler::findBlockAndMap(const double x, const double y, osgViewer::Viewer* viewer)
{
	if (!viewer->getSceneData())
		return std::make_pair(false, nullptr);	//nothing to pick

	osgUtil::LineSegmentIntersector* picker = new osgUtil::LineSegmentIntersector(
		osgUtil::Intersector::PROJECTION, x, y);

	osgUtil::IntersectionVisitor iv(picker);

	viewer->getCamera()->accept(iv);

	osg::ref_ptr<osg::Node> selectedBlock = nullptr;
	osg::ref_ptr<osg::Node> selectedMap = nullptr;

	//получить карту и блок
	Map* map = nullptr;
	Block* block = nullptr;

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

void MouseHandler::ReceiveBlock(TexType type, FillType fillType)
{
	_type = type;
	_fType = fillType;
}