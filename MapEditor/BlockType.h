#pragma once

#include <string>

enum class FillType		//block filling
{
  FULL,		//4 tiles
  RIGHT,	//2 tiles
  BOTTOM,
  LEFT,
  TOP
};

class BlockType
{
public:
  BlockType() = default;
  BlockType(std::string typeName, std::string texPath, 
    FillType fillType, bool isPassable, bool isUnderTank);
  ~BlockType();

  std::string GetTypeName() const { return _typeName; }
  std::string GetTexPath() const { return _texPath; }
  FillType GetFillType() const { return _fillType; }
  bool GetPassability() const { return _isPassable; }
  bool GetUnderTank() const { return _isUnderTank; }

  void GetBlockType(std::string& typeName, std::string& texPath,
    int& fillType, bool& isPassable, bool& isUnderTank) const;

  friend bool operator!=(BlockType& blockTypeLeft, BlockType& blockTypeRight);

private:
  std::string _typeName;   
  std::string _texPath;
  FillType _fillType; 
  bool _isPassable;   //is obstacle or not
  bool _isUnderTank;  //drawing under tank or not
};

