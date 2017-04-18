#include "MouseHandler.h"


MouseHandler::MouseHandler():
_mx(0), _my(0)
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
			double x = ea.getXnormalized();	//нормализация экранных координат для polytope intersector
			double y = ea.getYnormalized();

			if (pick(x, y, viewer))
				return true;	//true, чтобы обработать событие

		case(osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) :
			return true;
		}
		
		return false;
	}
	default:
		return false;
	}
}

bool MouseHandler::pick(const double x, const double y, osgViewer::Viewer* viewer)
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

	if (picker->containsIntersections())
	{
		osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;
		unsigned int idx = nodePath.size();

		//получить карту и блок
		Map* map = nullptr;
		Block* block = nullptr;
		//find block and map
		while (idx--)
		{
			if (block == nullptr)
				block = dynamic_cast<Block*>(nodePath[idx]);
			if (map == nullptr)
				map = dynamic_cast<Map*>(nodePath[idx]);

			if ((block == nullptr) || (map == nullptr));
			continue;

			//found the block in nodePath
			if (_selectedNode.valid())
			{
				//previous selected node
			}

			_selectedNode = block;
			break;
		}


		if ((map != nullptr) && (block != nullptr))
		{
			if (block->GetType() != TexType::BORDER)
			{
				block->SetBlock(_type, _fType);
			}
		}
			
		//if (block->GetType() != TexType::EMPTY)
		//map->removeChild(block);

		/*
		if (!_selectedNode.valid())
		{
		//pick failed
		//add block?
		}
		*/
	}
	/*
	else if (_selectedNode.valid())
	{
	//null
	}
	*/
	return _selectedNode.valid();
}

void MouseHandler::ReceiveBlock(TexType type, FillType fillType)
{
	_type = type;
	_fType = fillType;
}