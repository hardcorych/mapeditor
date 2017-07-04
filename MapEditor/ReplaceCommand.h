#pragma once

#include <qundostack.h>

#include <Map.h>

class ReplaceCommand : public QUndoCommand	//replace existing block on map
{
public:
  ReplaceCommand(osg::ref_ptr<Map> map,
    osg::ref_ptr<Block> block,
    BlockType blockType,
    QUndoCommand* parent = 0);
  ~ReplaceCommand();

  void undo() override;
  void redo() override;

private:
  //osg::ref_ptr<Block> _block = nullptr;
  osg::ref_ptr<Map> _map = nullptr;
  BlockType _blockType;
  BlockType _blockTypeOld;
  int _x;
  int _z;
};