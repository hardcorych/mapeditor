#include <osgViewer/Viewer>

#include "Map.h"

Map::Map(unsigned int sizeX, unsigned int sizeZ) :
    _sizeX(sizeX),
    _sizeZ(sizeZ),
    _step(16)
{
  //��������� ������ �����
  //������ �������� � ���������� ������ ������� �������

  //������������ ������
  generateBorder();
  generateGameArea();
}

Map::~Map()
{
}

void Map::GenerateEmptyMap(int sizeX, int sizeZ)		//�������� ����� �����
{
  if (_sizeX != sizeX) _sizeX = sizeX;
  if (_sizeZ != sizeZ) _sizeZ = sizeZ;
  generateBorder();
  generateGameArea();
}

void Map::generateBorder()
{
  //���������� ������������ �������
  _sizeX = (_sizeX + 3)*_step;	//��������� ����� ��� ����� +3 �� X
  _sizeZ = (_sizeZ + 2)*_step;	//��������� ����� ��� ����� +2 �� Z
  //������������ ������

  //���������� ������ ������� �������, ������� � ������ �������
  //������ �������

  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);
  BlockType borderBlock("BORDER",
                        "Resources/tiles/BORDER.png",
                        "FULL",
                        0,
                        0);

  for (int x = -_step; x < _sizeX - _step; x += _step)
  {
    addChild(new Block(x, -_step, borderBlock));
  }
  //������ �������
  for (int z = 0; z < _sizeZ - _step; z += _step)
  {
    for (int x = _sizeX - 3 * _step; x < _sizeX - _step; x += _step) 
    {
      addChild(new Block(x, z, borderBlock));
    }
  }
  //������� �������
  for (int x = _sizeX - 4 * _step; x >= -_step; x -= _step) 
  {
    addChild(new Block(x, _sizeZ - 2 * _step, borderBlock));
  }
  //����� �������
  for (int z = _sizeZ - 3 * _step; z > -_step; z -= _step) 
  {
    addChild(new Block(-_step, z, borderBlock));
  }

  _sizeX -= 3 * _step;	//�������� �������������� � ������� ������� �������
  _sizeZ -= 2 * _step;
}

void Map::generateGameArea()
{
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);
  BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);
  for (int z = 0; z < _sizeZ; z += _step)
  {
    for (int x = 0; x < _sizeX; x += _step)
    {
      //���������� ��������� ������� ������� �������
      addChild(new Block(x, z, emptyBlock));
    }
  }
}

void Map::Clear()		//�������� �����
{
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);

  removeChildren(0, getNumChildren());
}

void Map::AddBlock(int x, int z, const BlockType& blockType)
{
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);

  osg::ref_ptr<Block> blockOld = nullptr;

  osg::ref_ptr<Block> block = new Block(x, z, blockType);
  //����� �����, ������� ����� ��������
  for (int i = 0; i < getNumChildren(); i++)
  {
    blockOld = static_cast<Block*>(getChild(i));

    if (blockOld->GetX() == x &&
      blockOld->GetZ() == z && 
      blockOld->GetType().isNotBorderType())
    {
      replaceChild(blockOld, block);
    }
  }
}

void Map::RemoveBlock(int x, int z)
{
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);

  osg::ref_ptr<Block> block = nullptr;

  BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);

  for (int i = 0; i < getNumChildren(); i++) 
  {
    block = static_cast<Block*>(getChild(i));

    if (block->GetX() == x && block->GetZ() == z) 
    {
      replaceChild(block, new Block(x, z, emptyBlock));
    }
  }
}

Map::Blocks Map::SaveBlocksAndGet()
{
  Blocks savedBlocks;

  osg::ref_ptr<Block> block;

  for (int blockIndex = 0; blockIndex < getNumChildren(); blockIndex++)
  {
    block = static_cast<Block*>(getChild(blockIndex));

    BlockType blockType = block->GetType();

    if (blockType.isNotBorderType() && blockType.isNotEmptyType())
    {
      savedBlocks.push_back(block);
    }
  }

  return savedBlocks;
}

void Map::Resize(Blocks savedBlocks, int sizeX, int sizeZ)
{
  Clear();
  GenerateEmptyMap(sizeX, sizeZ);

  for (osg::ref_ptr<Block> block : savedBlocks)
  {
    AddBlock(block->GetX(), block->GetZ(), block->GetType());
  }
}

void Map::operator()(osgViewer::Viewer& viewer)
{
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);
  viewer.frame();
}
