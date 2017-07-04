#pragma once

#include <qundostack.h>

#include <Map.h>

class ChangeSizeCommand : public QUndoCommand	//change map size
{
public:
  ChangeSizeCommand(osg::ref_ptr<Map> map, int mapSizeX, int mapSizeZ,
    QUndoCommand* parent = 0);
  ~ChangeSizeCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Map> _map;

  int _mapSizeX;
  int _mapSizeZ;
  int _mapSizeXOld;
  int _mapSizeZOld;
  std::map<std::pair<int, int>, osg::ref_ptr<Block>> deletedBlocks;
};