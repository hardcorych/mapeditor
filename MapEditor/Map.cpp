#include "Map.h"

Map::Map(unsigned int sizeX, unsigned int sizeZ) :
    _sizeX(sizeX),
    _sizeZ(sizeZ),
    _step(16)
{
  //указанный размер карты
  //размер задается в количестве блоков игровой области

  //формирование границ
  generateBorder();
  generateGameArea();
}

Map::~Map()
{
}

void Map::GenerateEmptyMap(int sizeX, int sizeZ)		//создание новой карты
{
  if (_sizeX != sizeX) _sizeX = sizeX;
  if (_sizeZ != sizeZ) _sizeZ = sizeZ;
  generateBorder();
  generateGameArea();
}

void Map::generateBorder()
{
  //потайловое формирование границы
  _sizeX = (_sizeX + 3)*_step;	//выделение места под рамку +3 по X
  _sizeZ = (_sizeZ + 2)*_step;	//выделение места под рамку +2 по Z
  //формирование границ

  //заполнение против часовой стрелки, начиная с нижней границы
  //нижняя граница
  //int startBorder = -1 * _step;
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);
  BlockType borderBlock("BORDER", "Resources/tiles/BORDER.png", "FULL",
    0, 0);

  for (int x = -_step; x < _sizeX - _step; x += _step) {
    addChild(new Block(x, -_step, borderBlock));
  }
  //правая граница
  for (int z = 0; z < _sizeZ - _step; z += _step) {
    for (int x = _sizeX - 3 * _step; x < _sizeX - _step; x += _step) {
      addChild(new Block(x, z, borderBlock));
    }
  }
  //верхняя граница
  for (int x = _sizeX - 4 * _step; x >= -_step; x -= _step) {
    addChild(new Block(x, _sizeZ - 2 * _step, borderBlock));
  }
  //левая граница
  for (int z = _sizeZ - 3 * _step; z > -_step; z -= _step) {
    addChild(new Block(-_step, z, borderBlock));
  }

  _sizeX -= 3 * _step;	//обратное преобразование к размеру игровой области
  _sizeZ -= 2 * _step;
}

void Map::generateGameArea()
{
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);
  BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);
  for (int z = 0; z < _sizeZ; z += _step) {
    for (int x = 0; x < _sizeX; x += _step) {
      //заполнение свободной области пустыми блоками
      addChild(new Block(x, z, emptyBlock));
    }
  }
}

void Map::Clear()		//удаление карты
{
  //std::lock_guard<std::mutex> lgMutex(_mutex);
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);

  removeChildren(0, getNumChildren());
}


//void Map::AddBlock(osg::ref_ptr<Block> block)	//для чтения из файла
void Map::AddBlock(int x, int z, BlockType blockType)
{
  //std::lock_guard<std::mutex> lgMutex(_mutex);
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);

  osg::ref_ptr<Block> blockOld = nullptr;

  osg::ref_ptr<Block> block = new Block(x, z, blockType);
  //поиск блока, который нужно заменить
  for (int i = 0; i < getNumChildren(); i++)
  {
    blockOld = dynamic_cast<Block*>(getChild(i));
    //if (blockOld->GetX() == block->GetX() && 
      //blockOld->GetZ() == block->GetZ())
    if (blockOld->GetX() == x &&
      blockOld->GetZ() == z && 
      blockOld->GetType().GetTypeName() != "BORDER")
    {
      //blockOld->SetType(blockType);
      replaceChild(blockOld, block);
    }
  }
}

void Map::RemoveBlock(int x, int z)
{
  //std::lock_guard<std::mutex> lgMutex(_mutex);
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);

  osg::ref_ptr<Block> block = nullptr;

  BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);

  for (int i = 0; i < getNumChildren(); i++) {
    block = dynamic_cast<Block*>(getChild(i));

    if (block->GetX() == x && block->GetZ() == z) {
      replaceChild(block, new Block(x, z, emptyBlock));
    }
  }
}

std::vector<osg::ref_ptr<Block>> Map::SaveBlocksAndGet()
{
  std::vector<osg::ref_ptr<Block>> savedBlocks;

  osg::ref_ptr<Block> block;

  for (int blockIndex = 0; blockIndex < getNumChildren(); blockIndex++)
  {
    block = dynamic_cast<Block*>(getChild(blockIndex));

    bool isBorderBlock = 
      (block->GetType().GetTypeName() == "BORDER");
    bool isEmptyBlock =
      (block->GetType().GetTypeName() == "EMPTY");

    if (!isBorderBlock && !isEmptyBlock)
    {
      savedBlocks.push_back(block);
    }
  }

  return savedBlocks;
}

void Map::Resize(std::vector<osg::ref_ptr<Block>> savedBlocks,
                 int sizeX, 
                 int sizeZ)
{
  Clear();
  GenerateEmptyMap(sizeX, sizeZ);
  for (std::vector<osg::ref_ptr<Block>>::iterator it = savedBlocks.begin();
    it != savedBlocks.end(); ++it)
  {
    AddBlock((*it)->GetX(), (*it)->GetZ(), (*it)->GetType());
  }
}

/*
std::vector<osg::ref_ptr<Block>> Map::ResizeAndGetDeletedBlocks(
  std::vector<osg::ref_ptr<Block>> deletedBlocksOld,
  int sizeX,
  int sizeZ)
{
  //std::lock_guard<std::mutex> lgMutex(_mutex);
  std::lock_guard<std::recursive_mutex> lgMutex(_mutex);

  //перевод размера в осгшные единицы
  sizeX *= _step;
  sizeZ *= _step;

  //saving the not-border and not-empty blocks

  bool isNewSizeSame = (_sizeX == sizeX && _sizeZ == sizeZ);	//

  std::vector<osg::ref_ptr<Block>> deletedBlocks;

  if (!isNewSizeSame) {
    osg::ref_ptr<Block> block = nullptr;

    bool isBlockCoordsGreaterThanSize;
    bool isBorderBlock;

    for (int i = 0; i < getNumChildren(); i++) {
      block = dynamic_cast<Block*>(getChild(i));

      isBlockCoordsGreaterThanSize = 
        (block->GetX() >= sizeX || block->GetZ() >= sizeZ);

      isBorderBlock = (block->GetType().GetTypeName() == "BORDER");

      if (isBlockCoordsGreaterThanSize || isBorderBlock) {
        //удаление блоков вне игровой области и рамки
        if (!isBorderBlock)		//сохраняем, если не граничный блок
        {
          deletedBlocks.push_back(block);
        }          
        removeChild(block);
        i--;
      }
    }

    //resizing
    int oldSizeX = _sizeX;
    int oldSizeZ = _sizeZ;
    _sizeX = sizeX;
    _sizeZ = sizeZ;

    bool isNewSizeGreater = (_sizeX > oldSizeX || _sizeZ > oldSizeZ);

    if (isNewSizeGreater) {
      //заполнение сохраненными блоками
      if (!deletedBlocksOld.empty()) {
        std::vector<osg::ref_ptr<Block>>::iterator it;
        for (it = deletedBlocksOld.begin(); it != deletedBlocksOld.end(); ++it) {
          addChild(*it);
        }
      }
      //заполнение свободной области пустыми блоками
      else {
        BlockType emptyBlock("EMPTY", "", "FULL", 0, 0);

        for (int z = oldSizeZ; z < _sizeZ; z += _step) {
          for (int x = 0; x < _sizeX; x += _step) {
            addChild(new Block(x, z, emptyBlock));
          }
        }

        for (int z = _sizeZ - _step; z >= 0; z -= _step) {
          for (int x = oldSizeX; x < _sizeX; x += _step) {
            addChild(new Block(x, z, emptyBlock));
          }
        }        
      }
    }

    //перевод координат в блоки для построения новой рамки
    _sizeX /= _step;
    _sizeZ /= _step;
    setBorder();
  }
  return deletedBlocks;
}
*/