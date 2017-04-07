#pragma once

#include <osg/Group>
#include <Block.h>

//����� � XML-���� �� ������

class Map : public osg::Group
{
public:
	Map();
	Map(unsigned int size);
	~Map();

	void ReadFile();
	void SaveFile();

	void AddBlock();
	void RemoveBlock();

private:
	unsigned int _size;		//������ �����		
	const unsigned int _step;		//��� ������ ������� ������ �����
	
	std::vector<Tile> tiles;	//�����
};

