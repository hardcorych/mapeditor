#include "Map.h"


Map::Map() :
_step(16),	//��� ������
_sizeX(10), _sizeZ(10)
{
  setBorder();
  setGameArea();
}

Map::Map(unsigned int sizeX, unsigned int sizeZ) :
_sizeX(sizeX),
_sizeZ(sizeZ),
_step(16)
{
  //��������� ������ �����
  //������ �������� � ���������� ������ ������� �������
  //������������ ������
  setBorder();
  setGameArea();
}

Map::~Map()
{
}

void Map::Set(int sizeX, int sizeZ)		//�������� ����� �����
{
  if (_sizeX != sizeX) _sizeX = sizeX;
  if (_sizeZ != sizeZ) _sizeZ = sizeZ;
  setBorder();
  setGameArea();
}

void Map::setBorder()
{
  //���������� ������������ �������
  _sizeX = (_sizeX + 3)*_step;	//��������� ����� ��� ����� +3 �� X
  _sizeZ = (_sizeZ + 2)*_step;	//��������� ����� ��� ����� +2 �� Z
  //������������ ������
  //����� � 2 ���������, ������ ������� ������ ���� (��� �����?)

  //���������� ������ ������� �������, ������� � ������ �������
  //������ �������
  //int startBorder = -1 * _step;

  for (int x = -_step; x < _sizeX - _step; x += _step) {
    addChild(new Block(x, -_step, TexType::BORDER, FillType::FULL));
  }
  //������ �������
  for (int z = 0; z < _sizeZ - _step; z += _step) {
    for (int x = _sizeX - 3 * _step; x < _sizeX - _step; x += _step) {
      addChild(new Block(x, z, TexType::BORDER, FillType::FULL));
    }
  }
  //������� �������
  for (int x = _sizeX - 4 * _step; x >= -_step; x -= _step) {
    addChild(new Block(x, _sizeZ - 2 * _step, TexType::BORDER, FillType::FULL));
  }
  //����� �������
  for (int z = _sizeZ - 3 * _step; z > -_step; z -= _step) {
    addChild(new Block(-_step, z, TexType::BORDER, FillType::FULL));
  }

  _sizeX -= 3 * _step;	//�������� �������������� � ������� ������� �������
  _sizeZ -= 2 * _step;
}

void Map::setGameArea()
{
  for (int z = 0; z < _sizeZ; z += _step) {
    for (int x = 0; x < _sizeX; x += _step) {
      //���������� ��������� ������� ������� �������
      addChild(new Block(x, z, TexType::EMPTY, FillType::FULL));
    }
  }
}

void Map::Remove()		//�������� �����
{
  std::lock_guard<std::mutex> lgMutex(_mutex);

  removeChildren(0, getNumChildren());
}

void Map::AddBlock(osg::ref_ptr<Block> block, int x, int z)	//��� ������ �� �����
{
  std::lock_guard<std::mutex> lgMutex(_mutex);

  osg::ref_ptr<Block> blockOld = nullptr;

  //����� �����, ������� ����� ��������
  for (int i = 0; i < getNumChildren(); i++) {
    blockOld = dynamic_cast<Block*>(getChild(i));
    if (blockOld->GetX() == x && blockOld->GetZ() == z) {
      replaceChild(blockOld, block);
    }
  }
}

void Map::RemoveBlock(int x, int z)
{
  std::lock_guard<std::mutex> lgMutex(_mutex);

  osg::ref_ptr<Block> block = nullptr;

  for (int i = 0; i < getNumChildren(); i++) {
    block = dynamic_cast<Block*>(getChild(i));

    if (block->GetX() == x && block->GetZ() == z) {
      replaceChild(block, new Block(x, z, TexType::EMPTY, FillType::FULL));
    }
  }
}

std::map<std::pair<int, int>, osg::ref_ptr<Block>> Map::Resize(std::map<std::pair<int, int>, osg::ref_ptr<Block>> deletedBlocksOld,
  int sizeX, int sizeZ)
{
  std::lock_guard<std::mutex> lgMutex(_mutex);

  //������� ������� � ������� �������
  sizeX *= _step;
  sizeZ *= _step;

  bool isNewSizeSame = (_sizeX == sizeX && _sizeZ == sizeZ);	//������ ��������?

  std::map<std::pair<int, int>, osg::ref_ptr<Block>> deletedBlocks;

  if (!isNewSizeSame) {
    //Block* block = nullptr;
    osg::ref_ptr<Block> block = nullptr;

    bool isBlockCoordsMoreThanSize;
    bool isBorderBlock;

    for (int i = 0; i < getNumChildren(); i++) {
      block = dynamic_cast<Block*>(getChild(i));

      isBlockCoordsMoreThanSize = (block->GetX() >= sizeX || block->GetZ() >= sizeZ);
      isBorderBlock = (block->GetType() == TexType::BORDER);

      if (isBlockCoordsMoreThanSize || isBorderBlock) {
        //�������� ������ ��� ������� ������� � �����
        if (!isBorderBlock)		//���������, ���� �� ��������� ����
          deletedBlocks[std::make_pair(block->GetX(), block->GetZ())] = block;
        removeChild(block);
        i--;
      }
    }

    int oldSizeX = _sizeX;
    int oldSizeZ = _sizeZ;
    _sizeX = sizeX;
    _sizeZ = sizeZ;

    bool isNewSizeGreater = (_sizeX > oldSizeX || _sizeZ > oldSizeZ);

    if (isNewSizeGreater) {
      //���������� ��������� ������� ������� �������
      if (!deletedBlocksOld.empty()) {
        std::map<std::pair<int, int>, osg::ref_ptr<Block>>::iterator it;
        for (it = deletedBlocksOld.begin(); it != deletedBlocksOld.end(); ++it) {
          addChild(it->second);
        }
      }
      else {
        for (int z = oldSizeZ; z < _sizeZ; z += _step) {
          for (int x = 0; x < _sizeX; x += _step) {
            addChild(new Block(x, z, TexType::EMPTY, FillType::FULL));
          }
        }
        for (int z = oldSizeZ - _step; z >= 0; z -= _step) {
          for (int x = oldSizeX; x < _sizeX; x += _step) {
            addChild(new Block(x, z, TexType::EMPTY, FillType::FULL));
          }
        }
      }
    }

    //������� ��������� � ����� ��� ���������� ����� �����
    _sizeX /= _step;
    _sizeZ /= _step;
    setBorder();
  }
  return deletedBlocks;
}