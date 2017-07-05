#include "BlockType.h"

BlockType::BlockType(std::string typeName,
                     std::string texPath,
                     std::string fillType, 
                     bool isPassable, 
                     bool isUnderTank):
    _typeName(typeName),
    _texPath(texPath),
    _fillType(fillType),
    _isPassable(isPassable),
    _isUnderTank(isUnderTank)
{
}

BlockType::~BlockType()
{
}

bool operator!=(BlockType& blockTypeLeft, BlockType& blockTypeRight)
{
  if (blockTypeLeft._typeName != blockTypeRight._typeName)
    return true;
  else if (blockTypeLeft._fillType != blockTypeRight._fillType)
    return true;
  else if (blockTypeLeft._texPath != blockTypeRight._texPath)
    return true;
  else if (blockTypeLeft._isPassable != blockTypeRight._isPassable)
    return true;
  else if (blockTypeLeft._isUnderTank != blockTypeRight._isUnderTank)
    return true;
  else
    return false;
}

