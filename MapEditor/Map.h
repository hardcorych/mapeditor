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

	void ReadFile();
	void SaveFile();

private:
	int _sizeX;
	int _sizeZ;
	unsigned int _size;		//������ �����. �������� ������ �������, ����� ���������� �� 16(������� � �����)	
	int _step;		//��� ������ ������� ������ �����/�����

	//std::map<std::pair<int, int>, osg::ref_ptr<Block>> blockMap;	//����� ��� ����������� ������ ������ ��� ������ ����� � �����

	void setBorder();
	void setGameArea();
};

