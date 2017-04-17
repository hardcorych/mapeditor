#pragma once

#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgUtil/PolytopeIntersector>
#include <Block.h>

class MouseHandler : public osgGA::GUIEventHandler
{
public:
	MouseHandler();
	~MouseHandler();

	//добавление блока по левой кнопке мыши
	//удаление блока по правой кнопке мыши
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		if (!viewer) return false;

		switch (ea.getEventType())	//получаем событие
		{
		case(osgGA::GUIEventAdapter::PUSH):
		case(osgGA::GUIEventAdapter::MOVE) :
		{
			_mx = ea.getX();
			_my = ea.getY();
			return false;
		}
		case(osgGA::GUIEventAdapter::RELEASE):
		{
			double x = ea.getX();	//получает координаты относительно вьювера
			double y = ea.getY();
			x = ea.getXnormalized();
			y = ea.getYnormalized();

			if (pick(x, y, viewer))
				return true;	//true, чтобы обработать событие
			return false;
		}
		default:
			return false;
		}
	}

protected:
	double _mx, _my;	//mouse coords
	osg::ref_ptr<osg::Node> _selectedNode;	//для получения узла из пересечений

	bool pick(const double x, const double y,
		osgViewer::Viewer* viewer)
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

			
			//find the block
			while (idx--)
			{
				Block* block = dynamic_cast<Block*>(nodePath[idx]);
				if (block == nullptr)
					continue;


				//found the block in nodePath
				if (_selectedNode.valid())
				{
					//previous selected node
				}

				_selectedNode = block;
				//remove block?
				break;
			}

			if (!_selectedNode.valid())
			{
				//pick failed
				//add block?
			}
		}
		else if (_selectedNode.valid())
		{
			//null
		}
		return _selectedNode.valid();
	}
};

