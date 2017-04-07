#pragma once

#include <osg/Group>

class Map : public osg::Group
{
public:
	Map();
	Map(unsigned int size);
	~Map();

private:
	unsigned int _size;		//размер карты		
};

