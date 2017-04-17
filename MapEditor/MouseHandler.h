#pragma once

#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgUtil/PolytopeIntersector>
#include <Block.h>
#include <Map.h>
#include <qobject.h>

class MouseHandler : public QObject, public osgGA::GUIEventHandler
{
	Q_OBJECT
public:
	MouseHandler();
	~MouseHandler();

	//добавление блока по левой кнопке мыши
	//удаление блока по правой кнопке мыши
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

protected:
	double _mx, _my;	//mouse coords
	osg::ref_ptr<osg::Node> _selectedNode;	//для получения узла из пересечений

	TexType _type;
	FillType _fType;
	
	//операции с блоками
	void addBlock();
	void removeBlock();
	void changeBlock();

	bool pick(const double x, const double y, osgViewer::Viewer* viewer);
	
	public slots:
	void ReceiveBlock(TexType type, FillType fillType);
};

