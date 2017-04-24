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

	std::pair<bool, Block*> findBlockAndMap(const double x, const double y, osgViewer::Viewer* viewer);	

signals:
	void AddableBlock(Block* block, TexType type, FillType fType);
	void RemovableBlock(Block* block);

	public slots:
	void ReceiveBlock(TexType type, FillType fillType);
};

