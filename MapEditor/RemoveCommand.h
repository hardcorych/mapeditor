#pragma once

#include <qundostack.h>

#include <Map.h>

class RemoveCommand : public QUndoCommand	//remove block from map
{
public:
  RemoveCommand(osg::ref_ptr<Map> map,
    int x, int z, BlockType blockType, QUndoCommand* parent = 0);
  ~RemoveCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Map> _map;
  //osg::ref_ptr<Block> _block = nullptr;
  int _x;
  int _z;
  BlockType _blockType;
};