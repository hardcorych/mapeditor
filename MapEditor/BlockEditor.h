#pragma once

#include <osg/Node>

#include <Block.h>
#include <Editor.h>

struct BlockType
{
  QString leftBottomTexture;
  QString leftTopTexture;
  QString rightTopTexture;
  QString rightBottomTexture;

  bool isPassable;
  bool isUnderTank;
};

class BlockEditor : public Editor
{
public:
  BlockEditor() = default;
  virtual ~BlockEditor() = default;
  //loadBlock ?
  //saveBlock ?

private:
  osg::ref_ptr<Block> _block = nullptr;
  
  //loadBlock
  //setTexture
  //setPassability
};