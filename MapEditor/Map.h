#pragma once

#include <mutex>

#include <osg/Group>

#include <qstring.h>

#include <Block.h>

class Map : public osg::Group
{
public:
  Map() = delete;
  Map(unsigned int sizeX, unsigned int sizeZ);

protected:
  ~Map();

public:
  inline int GetSizeX() const;
  inline int GetSizeZ() const;

  inline QString GetSizeX_str() const;
  inline QString GetSizeZ_str() const;

  void GenerateEmptyMap(int sizeX, int sizeZ);
  void Clear();

  void AddBlock(int x, int z, BlockType blockType);
  void RemoveBlock(int x, int z);

  //resizing
  std::vector<osg::ref_ptr<Block>> SaveBlocksAndGet();
  void Resize(std::vector<osg::ref_ptr<Block>> savedBlocks,
    int sizeX,
    int sizeZ);

  //std::mutex& GetMutex() { return std::ref(_mutex); }
  std::recursive_mutex& GetMutex() { return std::ref(_mutex); }

private:
  //generateBorder
  //generateGameArea
  void generateBorder();
  void generateGameArea();

private:
  int _sizeX;
  int _sizeZ;
  int _step;		//step equals block size

  //std::mutex _mutex;
  std::recursive_mutex _mutex;
};

inline int Map::GetSizeX() const	
{ 
  return _sizeX / _step; 
}

inline int Map::GetSizeZ() const
{ 
  return _sizeZ / _step;
}

inline QString Map::GetSizeX_str() const
{ 
  return QString::number(_sizeX); 
}	//size in blocks

inline QString Map::GetSizeZ_str() const
{ 
  return QString::number(_sizeZ);
}


