#pragma once
#include <BlockType.h>

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

bool operator!=(BlockType& blockTypeLeft, BlockType& blockTypeRight)
{
  if (blockTypeLeft._typeName != blockTypeRight._typeName ||
      blockTypeLeft._fillType != blockTypeRight._fillType ||
      blockTypeLeft._texPath != blockTypeRight._texPath ||
      blockTypeLeft._isPassable != blockTypeRight._isPassable ||
      blockTypeLeft._isUnderTank != blockTypeRight._isUnderTank)
    return true;
  else
    return false;
}

bool operator==(BlockType& blockTypeLeft, BlockType& blockTypeRight)
{
  if (blockTypeLeft._typeName == blockTypeRight._typeName &&
      blockTypeLeft._fillType == blockTypeRight._fillType &&
      blockTypeLeft._texPath == blockTypeRight._texPath &&
      blockTypeLeft._isPassable == blockTypeRight._isPassable &&
      blockTypeLeft._isUnderTank == blockTypeRight._isUnderTank)
    return true;
  else
    return false;
}

