#pragma once

#include <qundostack.h>

#include <BlockType.h>
#include <Map.h>

class AddCommand : public QUndoCommand	//add block on map
{
public:
  AddCommand(osg::ref_ptr<Map> map, 
             int x,
             int z,
             const BlockType& blockType,
             QUndoCommand* parent = nullptr);
  ~AddCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Map> _map;
  int _x;
  int _z;
  BlockType _blockType;
};