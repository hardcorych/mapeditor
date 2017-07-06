#pragma once

#include <qundostack.h>

#include <Map.h>

class RemoveCommand : public QUndoCommand	//remove block from map
{
public:
  RemoveCommand(osg::ref_ptr<Map> map,
                int x, 
                int z,
                const BlockType& blockType, 
                QUndoCommand* parent = 0);
  ~RemoveCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Map> _map;
  int _x;
  int _z;
  BlockType _blockType;
};