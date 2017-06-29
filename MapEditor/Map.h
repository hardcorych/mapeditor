#pragma once

#include <mutex>

#include <osg/Group>

#include <qstring.h>

#include <Block.h>

class Map : public osg::Group
{
public:
  Map();
  Map(unsigned int sizeX, unsigned int sizeZ);
  ~Map();

  const int GetSizeX()	{ return _sizeX; }
  const int GetSizeZ()	{ return _sizeZ; }

  QString GetSizeX_str()	{ return QString::number(_sizeX); }	//size in blocks
  QString GetSizeZ_str()	{ return QString::number(_sizeZ); }

  void Set(int sizeX, int sizeZ);
  void Remove();

  //void AddBlock(osg::ref_ptr<Block> block, int x, int z);
  void AddBlock(osg::ref_ptr<Block> block);
  void RemoveBlock(int x, int z);

  //resizing
  std::map<std::pair<int, int>, osg::ref_ptr<Block>> Resize
    (std::map<std::pair<int, int>, osg::ref_ptr<Block>> deletedBlocksOld,
    int sizeX, int sizeZ);

  std::mutex& GetMutex() { return std::ref(_mutex); }

  std::string GetTexPath(std::string type);

private:
  int _sizeX;
  int _sizeZ;
  int _step;		//step equals block size

  std::mutex _mutex;

  void setBorder();
  void setGameArea();
};

