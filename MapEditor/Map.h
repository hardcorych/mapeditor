#pragma once

#include <osg/Group>
#include <Block.h>

//����� � XML-���� �� ������

class Map : public osg::Group
{
public:
	Map();
	Map(unsigned int sizeX, unsigned int sizeZ);
	~Map();

	void ReadFile();
	void SaveFile();


private:
	int _sizeX;
	int _sizeZ;
	unsigned int _size;		//������ �����. �������� ������ �������, ����� ���������� �� 16(������� � �����) ��� 8 (������� � �����)	
	int _step;		//��� ������ ������� ������ �����/�����

	void setBorder();
	void setGameArea();
};

