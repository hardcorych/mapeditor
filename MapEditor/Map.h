#pragma once

#include <osg/Group>
#include <Block.h>
#include <qstring.h>

//����� � XML-���� �� ������

class Map : public osg::Group
{
public:
	Map();
	Map(unsigned int sizeX, unsigned int sizeZ);
	~Map();

	const int GetSizeX()	{ return _sizeX; }
	const int GetSizeZ()	{ return _sizeZ; }

	QString GetSizeX_str()	{ return QString::number(_sizeX); }	//������ � ������
	QString GetSizeZ_str()	{ return QString::number(_sizeZ); }

	void Set(int sizeX, int sizeZ);
	void Remove();
	void AddBlock(osg::ref_ptr<Block> block, int x, int z);

	//�������������� ������� ����� ����� ������ ����������
	void Restore(std::map<std::pair<int, int>, osg::ref_ptr<Block>>, int sizeX, int sizeZ);	

	//resizing
	//void Resize(int sizeX, int sizeZ);
	//���������� ����� ��������� ������
	std::map<std::pair<int, int>, osg::ref_ptr<Block>> Resize(int sizeX, int sizeZ);

	//osg::ref_ptr<Map> operator=(Map map);

private:
	int _sizeX;
	int _sizeZ;	
	int _step;		//��� ������ ������� ������ �����/�����

	void setBorder();
	void setGameArea();
};

