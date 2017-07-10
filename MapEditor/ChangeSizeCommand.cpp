#pragma once

#include <ChangeSizeCommand.h>

ChangeSizeCommand::ChangeSizeCommand(Map& map,
                                     int mapSizeX,
                                     int mapSizeZ,
                                     QUndoCommand* parent) :
  QUndoCommand(parent),
  _map(map),
  _mapSizeX(mapSizeX),
  _mapSizeZ(mapSizeZ)
{
  _mapSizeXOld = _map.GetSizeX();
  _mapSizeZOld = _map.GetSizeZ();
  _savedBlocks = _map.SaveBlocksAndGet();
}

ChangeSizeCommand::~ChangeSizeCommand()
{
}

void ChangeSizeCommand::undo()
{
  //set old map
  _map.Resize(_savedBlocks, _mapSizeXOld, _mapSizeZOld);
}

void ChangeSizeCommand::redo()
{
  //set new map size
  _map.Resize(_savedBlocks, _mapSizeX, _mapSizeZ);
}