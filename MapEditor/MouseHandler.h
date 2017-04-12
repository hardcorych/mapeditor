#pragma once

#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgUtil/PolytopeIntersector>

class MouseHandler : public osgGA::GUIEventHandler
{
public:
	MouseHandler();
	~MouseHandler();

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
			x + y;
			return true;	//true, чтобы обработать событие
		}
		default:
			return false;
		}
	}

protected:
	double _mx, _my;	//mouse coords

	bool pick(const double x, const double y,
		osgViewer::Viewer* viewer)
	{
		if (!viewer->getSceneData())
			return false;	//nothing to pick

		double w(.05), h(.05);
		
		//преобразование координат через пересечения?
		osgUtil::PolytopeIntersector* picker =
			new osgUtil::PolytopeIntersector(
			osgUtil::Intersector::PROJECTION,
			x - w, y - h, x + w, y + h);

		osgUtil::IntersectionVisitor iv(picker);

		viewer->getCamera()->accept(iv);

		if (picker->containsIntersections())
		{
			osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;
			unsigned int idx = nodePath.size();

			//find the last group?
			while (idx--)
			{
				osg::Group* group = dynamic_cast<osg::Group*>(nodePath[idx]);
				if (group == nullptr)
					continue;

				//found the group in nodePath

			}
		}
	}
};

