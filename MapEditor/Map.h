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

	void AddBlock();
	void RemoveBlock();

private:
	int _sizeX;
	int _sizeZ;
	unsigned int _size;		//������ �����. �������� ������ �������, ����� ���������� �� 16(������� � �����) ��� 8 (������� � �����)	
	const int _step;		//��� ������ ������� ������ �����
	
	std::vector<osg::ref_ptr<Tile>> tiles;	//�����
	//Tile tile;
	osg::ref_ptr<Tile> tile = new Tile;
	std::map<std::pair<int, int>, osg::ref_ptr<Tile>> tileMap;
	//std::map<std::pair<unsigned int, unsigned int>, TileType> tileMap;
	//std::map<std::pair<unsigned int, unsigned int>, BlockType> blockMap;

	void setBorder();
};

