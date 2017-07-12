#pragma once

#include <mutex>

#include <osg/Group>

#include <qstring.h>

#include "Block.h"

class BlockType;

namespace osgViewer
{
  class Viewer;
}

class Map : public osg::Group
{
public:
  typedef std::vector<osg::ref_ptr<Block>> Blocks;

public:
  Map() = delete;
  Map(const Map&) = delete;
  Map(unsigned int sizeX, unsigned int sizeZ);

  Map& operator=(const Map&) = delete;
protected:
  ~Map() = default;

public:
  inline int GetSizeX() const;
  inline int GetSizeZ() const;

  inline QString GetSizeX_str() const;
  inline QString GetSizeZ_str() const;

  void GenerateEmptyMap(int sizeX, int sizeZ);
  void Clear();

  void AddBlock(int x, int z, const BlockType& blockType);
  void RemoveBlock(int x, int z);

  //resizing
  Blocks SaveBlocksAndGet();
  void Resize(Blocks savedBlocks, int sizeX, int sizeZ);

  void ViewerFrame(osgViewer::Viewer& viewer);

private:
  void generateBorder();
  void generateGameArea();

private:
  int _sizeX;
  int _sizeZ;
  int _step;		//step equals block size

  std::mutex _mutex;
};

//size in blocks
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
  return QString::number(_sizeX / _step);   
}	

inline QString Map::GetSizeZ_str() const
{ 
  return QString::number(_sizeZ / _step);
}

