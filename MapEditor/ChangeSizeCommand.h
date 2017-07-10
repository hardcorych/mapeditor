#pragma once

#include <qundostack.h>

#include <Map.h>

class ChangeSizeCommand : public QUndoCommand	//change map size
{
public:
  ChangeSizeCommand(Map& map, 
                    int mapSizeX,
                    int mapSizeZ,
                    QUndoCommand* parent = nullptr);
  ~ChangeSizeCommand();

  void undo() override;
  void redo() override;

private:
  Map& _map;

  int _mapSizeX;
  int _mapSizeZ;
  int _mapSizeXOld;
  int _mapSizeZOld;
  Map::Blocks _savedBlocks;
};