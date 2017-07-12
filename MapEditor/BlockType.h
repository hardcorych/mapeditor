#pragma once

#include <string>

#include <qstring.h>

class BlockType
{
public:

public:
  BlockType() = default;
  BlockType(const BlockType&) = default;
  BlockType(std::string typeName, 
            std::string texPath,
            std::string fillType, 
            bool isPassable, 
            bool isUnderTank);
  ~BlockType() = default;

  BlockType& operator=(const BlockType&) = default;
public:
  inline std::string GetTypeName() const;
  inline std::string GetTexPath() const;
  inline std::string GetFillType() const;
  inline bool GetPassability() const;
  inline bool GetUnderTank() const;

  inline void SetTypeName(std::string typeName);
  inline void SetTexPath(std::string texPath);
  inline void SetFillType(std::string fillType);
  inline void SetPassability(bool isPassable);
  inline void SetUnderTank(bool isUnderTank);

  friend bool operator!=(BlockType& blockTypeLeft, BlockType& blockTypeRight);
  friend bool operator==(BlockType& blockTypeLeft, BlockType& blockTypeRight);

  inline bool isBorderType() const;
  inline bool isEmptyType() const;
  inline bool isNotBorderType() const;
  inline bool isNotEmptyType() const;

  inline bool isFillFull() const;
  inline bool isFillLeft() const;
  inline bool isFillTop() const;
  inline bool isFillBottom() const;
  inline bool isFillRight() const;

  inline bool isNoData() const;

private:
  std::string _typeName;
  std::string _texPath;
  std::string _fillType;
  bool _isPassable;   //is obstacle or not
  bool _isUnderTank;  //drawing under tank or not
};

inline std::string BlockType::GetTypeName() const 
{ 
  return _typeName;
}

inline std::string BlockType::GetTexPath() const 
{ 
  return _texPath;
}

inline std::string BlockType::GetFillType() const
{ 
  return _fillType;
}

inline bool BlockType::GetPassability() const
{ 
  return _isPassable;
}

inline bool BlockType::GetUnderTank() const
{ 
  return _isUnderTank;
}

inline void BlockType::SetTypeName(std::string typeName)
{ 
  _typeName = typeName;
}

inline void BlockType::SetTexPath(std::string texPath)
{ 
  _texPath = texPath;
}

inline void BlockType::SetFillType(std::string fillType)
{ 
  _fillType = fillType;
}

inline void BlockType::SetPassability(bool isPassable)
{ 
  _isPassable = isPassable;
}

inline void BlockType::SetUnderTank(bool isUnderTank)
{ 
  _isUnderTank = isUnderTank;
}

inline bool BlockType::isNoData() const
{
  return (_typeName.empty() && _texPath.empty() && _fillType.empty());
}

inline bool BlockType::isBorderType() const
{
  return (_typeName == "BORDER");
}

inline bool BlockType::isEmptyType() const
{
  return (_typeName == "EMPTY");
}

inline bool BlockType::isNotBorderType() const
{
  return !(_typeName == "BORDER");
}

inline bool BlockType::isNotEmptyType() const
{
  return !(_typeName == "EMPTY");
}

inline bool BlockType::isFillFull() const
{
  return (_fillType == "FULL");
}

inline bool BlockType::isFillLeft() const
{
  return (_fillType == "LEFT");
}

inline bool BlockType::isFillTop() const
{
  return (_fillType == "TOP");
}

inline bool BlockType::isFillBottom() const
{
  return (_fillType == "BOTTOM");
}

inline bool BlockType::isFillRight() const
{
  return (_fillType == "RIGHT");
}