#pragma once

#include <osg/Group>
#include <Block.h>

//вывод в XML-файл по тайлам

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
	unsigned int _size;		//размер карты. задается любыми цифрами, затем умножается на 16(перевод в блоки) или 8 (перевод в тайлы)	
	int _step;		//шаг равный размеру одного блока/тайла

	void setBorder();
	void setGameArea();
};

