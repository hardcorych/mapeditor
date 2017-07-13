#pragma once

#include <qundostack.h>

#include <Map.h>

///change map size
class ChangeSizeCommand : public QUndoCommand	
{
public:
  ChangeSizeCommand() = delete;
  ChangeSizeCommand(const ChangeSizeCommand&) = delete;
  ChangeSizeCommand(Map& map, 
                    int mapSizeX,
                    int mapSizeZ,
                    QUndoCommand* parent = nullptr);
  ~ChangeSizeCommand() = default;

  ChangeSizeCommand& operator=(const ChangeSizeCommand&) = delete;

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