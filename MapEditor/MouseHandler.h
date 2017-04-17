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

	//���������� ����� �� ����� ������ ����
	//�������� ����� �� ������ ������ ����
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

protected:
	double _mx, _my;	//mouse coords
	osg::ref_ptr<osg::Node> _selectedNode;	//��� ��������� ���� �� �����������

	TexType _type;
	FillType _fType;
	
	//�������� � �������
	void addBlock();
	void removeBlock();
	void changeBlock();

	bool pick(const double x, const double y, osgViewer::Viewer* viewer);
	
	public slots:
	void ReceiveBlock(TexType type, FillType fillType);
};

