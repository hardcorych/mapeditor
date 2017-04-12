#pragma once

#include <osgGA/GUIEventHandler>

class MouseHandler : public osgGA::GUIEventHandler
{
public:
	MouseHandler() : _mx(0), _my(0) 
	{};
	~MouseHandler()
	{};

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{

	}

protected:
	double _mx, _my;	//mouse coords
};

