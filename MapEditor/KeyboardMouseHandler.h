#pragma once

#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgUtil/PolytopeIntersector>
#include <Block.h>
#include <Map.h>
#include <qobject.h>

class KeyboardMouseHandler : public QObject, public osgGA::GUIEventHandler
{
	Q_OBJECT
public:
	KeyboardMouseHandler();
	~KeyboardMouseHandler();

	//���������� ����� �� ����� ������ ����
	//�������� ����� �� ������ ������ ����
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

protected:
	double _mouseX, _mouseY;	//mouse coords

	TexType _type;
	FillType _fType;

	std::pair<bool, Block*> findBlockAndMap(const double x, const double y, osgViewer::Viewer* viewer);

signals:
	void AddableBlock(Block* block, TexType type, FillType fType);
	void RemovableBlock(Block* block);
	void ReplaceableBlock(Block* block, TexType type, FillType fType);
	void Undo();
	void Redo();

	public slots:
	void ReceiveBlock(TexType type, FillType fillType);
};
