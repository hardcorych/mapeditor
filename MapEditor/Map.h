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

	void AddBlock(int x, int z, BlockType type);
	void RemoveBlock(int x, int z);

private:
	int _sizeX;
	int _sizeZ;
	unsigned int _size;		//������ �����. �������� ������ �������, ����� ���������� �� 16(������� � �����) ��� 8 (������� � �����)	
	int _step;		//��� ������ ������� ������ �����/�����
	
	//std::map<std::pair<int, int>, osg::ref_ptr<Tile>> tileMap;	//�����, ���� - ���������� XZ
	//���� �� blockMap?
	std::map<std::pair<int, int>, osg::ref_ptr<Block>> blockMap;	//�����, ���� - ���������� XZ

	void setBorder();
	void setGameArea();
};

