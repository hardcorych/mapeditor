#include "BlockType.h"

BlockType::BlockType(std::string typeName, std::string texPath,
  FillType fillType, bool isPassable, bool isUnderTank):
  _typeName(typeName),
  _texPath(texPath),
  _fillType(fillType),
  _isPassable(isPassable),
  _isUnderTank(isUnderTank)
{
}

void BlockType::GetBlockType(std::string& typeName, std::string& texPath,
  int& fillType, bool& isPassable, bool& isUnderTank) const
{
  typeName = _typeName;
  texPath = _texPath;
  fillType = (int)_fillType;
  isPassable = _isPassable;
  isUnderTank = _isUnderTank;
}

BlockType::~BlockType()
{
}

QString BlockType::GetFillType_str() const 
{
  switch (_fillType)
  {
  case FillType::FULL:
    return "FULL";
  case FillType::LEFT:
    return "LEFT";
  case FillType::RIGHT:
    return "RIGHT";
  case FillType::TOP:
    return "TOP";
  case FillType::BOTTOM:
    return "BOTTOM";
  default:
    break;
  }
  return "";
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

