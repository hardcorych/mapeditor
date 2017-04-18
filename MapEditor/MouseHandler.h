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
	double _mouseX, _mouseY;	//mouse coords

	TexType _type;
	FillType _fType;
	
	//операции с блоками
	//void addBlock();
	//void removeBlock();
	//void changeBlock();

	bool setBlock(const double x, const double y, osgViewer::Viewer* viewer);
	bool removeBlock(const double x, const double y, osgViewer::Viewer* viewer);
	bool findBlockAndSet(const double x, const double y, osgViewer::Viewer* viewer,
		void(Block::*BlockOperation)(TexType type, FillType fillType));		//callback

	public slots:
	void ReceiveBlock(TexType type, FillType fillType);
};

