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
	case(osgGA::GUIEventAdapter::RELEASE) :
	{
		switch (ea.getButton())
		{
		case(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON):
			//добавление/изменение блока
			_mouseX = ea.getXnormalized();	//нормализация экранных координат для polytope intersector
			_mouseY = ea.getYnormalized();

			if (setBlock(_mouseX, _mouseY, viewer))
				return true;	//true, чтобы обработать событие

		case(osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) :
			//удаление блока
			_mouseX = ea.getXnormalized();	//нормализация экранных координат для polytope intersector
			_mouseY = ea.getYnormalized();

			if (removeBlock(_mouseX, _mouseY, viewer))
				return true;
		}
		
		return false;
	}
	default:
		return false;
	}
}

bool MouseHandler::findBlockAndSet(const double x, const double y, osgViewer::Viewer* viewer,
	void(Block::*BlockOperation)(TexType type, FillType fillType))
{
	if (!viewer->getSceneData())
		return false;	//nothing to pick

	double w(.025), h(.025);		//площадь "пирамиды"

	//преобразование координат через пересечения?
	osgUtil::PolytopeIntersector* picker =
		new osgUtil::PolytopeIntersector(
		osgUtil::Intersector::PROJECTION,
		x - w, y - h, x + w, y + h);

	osgUtil::IntersectionVisitor iv(picker);

	viewer->getCamera()->accept(iv);

	//osgUtil::PolytopeIntersector::Intersections intersections;		//!!!
	osg::ref_ptr<osg::Node> selectedBlock = new osg::Node;
	osg::ref_ptr<osg::Node> selectedMap = new osg::Node;

	if (picker->containsIntersections())
	{
		osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;
		unsigned int idx = nodePath.size();

		//получить карту и блок
		Map* map = nullptr;
		Block* block = nullptr;

		//find block and map
		while ((idx--) && ((block == nullptr) || (map == nullptr)))
		{
			if (block == nullptr)
				block = dynamic_cast<Block*>(nodePath[idx]);
			if (map == nullptr)
				map = dynamic_cast<Map*>(nodePath[idx]);

			//if ((block == nullptr) || (map == nullptr));
			//continue;

			//break;
		}

		selectedBlock = block;
		selectedMap = map;

		if ((map != nullptr) && (block != nullptr))
		{
			if (block->GetType() != TexType::BORDER)
			{
				//block->SetBlock(_type, _fType);
				//BlockOperation
				//block->BlockOperation(_type, _fType);
			}
		}
	}
	return (selectedBlock.valid() && selectedMap.valid());
}

bool MouseHandler::setBlock(const double x, const double y, osgViewer::Viewer* viewer)
{
	if (!viewer->getSceneData())
		return false;	//nothing to pick

	double w(.025), h(.025);		//площадь "пирамиды"

	//преобразование координат через пересечения?
	osgUtil::PolytopeIntersector* picker =
		new osgUtil::PolytopeIntersector(
		osgUtil::Intersector::PROJECTION,
		x - w, y - h, x + w, y + h);

	osgUtil::IntersectionVisitor iv(picker);

	viewer->getCamera()->accept(iv);

	//osgUtil::PolytopeIntersector::Intersections intersections;		//!!!
	osg::ref_ptr<osg::Node> selectedBlock = new osg::Node;
	osg::ref_ptr<osg::Node> selectedMap = new osg::Node;

	if (picker->containsIntersections())
	{
		osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;
		unsigned int idx = nodePath.size();

		//получить карту и блок
		Map* map = nullptr;
		Block* block = nullptr;

		//find block and map
		while ((idx--) && ((block == nullptr) || (map == nullptr)))
		{
			if (block == nullptr)
				block = dynamic_cast<Block*>(nodePath[idx]);
			if (map == nullptr)
				map = dynamic_cast<Map*>(nodePath[idx]);
		}

		selectedBlock = block;
		selectedMap = map;

		if ((map != nullptr) && (block != nullptr))
		{
			if (block->GetType() != TexType::BORDER)
			{
				block->SetBlock(_type, _fType);
			}
		}
	}
	return (selectedBlock.valid() && selectedMap.valid());
}

bool MouseHandler::removeBlock(const double x, const double y, osgViewer::Viewer* viewer)
{
	if (!viewer->getSceneData())
		return false;	//nothing to pick

	double w(.025), h(.025);		//площадь "пирамиды"

	//преобразование координат через пересечения?
	osgUtil::PolytopeIntersector* picker =
		new osgUtil::PolytopeIntersector(
		osgUtil::Intersector::PROJECTION,
		x - w, y - h, x + w, y + h);

	osgUtil::IntersectionVisitor iv(picker);

	viewer->getCamera()->accept(iv);

	//osgUtil::PolytopeIntersector::Intersections intersections;		//!!!
	osg::ref_ptr<osg::Node> selectedBlock = new osg::Node;
	osg::ref_ptr<osg::Node> selectedMap = new osg::Node;

	if (picker->containsIntersections())
	{
		osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;
		unsigned int idx = nodePath.size();

		//получить карту и блок
		Map* map = nullptr;
		Block* block = nullptr;

		//find block and map
		while ((idx--) && ((block == nullptr) || (map == nullptr)))
		{
			if (block == nullptr)
				block = dynamic_cast<Block*>(nodePath[idx]);
			if (map == nullptr)
				map = dynamic_cast<Map*>(nodePath[idx]);
		}

		selectedBlock = block;
		selectedMap = map;

		if ((map != nullptr) && (block != nullptr))
		{
			if (block->GetType() != TexType::BORDER)
			{
				block->SetBlock(TexType::EMPTY, FillType::FULL);
			}
		}
	}

	return (selectedBlock.valid() && selectedMap.valid());
}

void MouseHandler::ReceiveBlock(TexType type, FillType fillType)
{
	_type = type;
	_fType = fillType;
}