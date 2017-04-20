#pragma once

#include <osg/Group>
#include <Block.h>
#include <qstring.h>

//вывод в XML-файл по тайлам

class Map : public osg::Group
{
public:
	Map();
	Map(unsigned int sizeX, unsigned int sizeZ);
	~Map();

	const int GetSizeX()	{ return _sizeX; }
	const int GetSizeZ()	{ return _sizeZ; }

	QString GetSizeX_str()	{ return QString::number(_sizeX); }	//размер в блоках
	QString GetSizeZ_str()	{ return QString::number(_sizeZ); }

	void Set(int sizeX, int sizeZ);
	void Remove();
	void AddBlock(osg::ref_ptr<Block> block, int x, int z);

	void ReadFile();
	void SaveFile();

private:
	int _sizeX;
	int _sizeZ;
	unsigned int _size;		//размер карты. задается любыми цифрами, затем умножается на 16(перевод в блоки)	
	int _step;		//шаг равный размеру одного блока/тайла

	//std::map<std::pair<int, int>, osg::ref_ptr<Block>> blockMap;	//карта для расстановки пустых блоков при чтении карты с файла

	void setBorder();
	void setGameArea();
};

