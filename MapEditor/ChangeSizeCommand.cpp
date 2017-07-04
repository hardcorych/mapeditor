#pragma once

#include <ChangeSizeCommand.h>

ChangeSizeCommand::ChangeSizeCommand(osg::ref_ptr<Map> map,
  int mapSizeX, int mapSizeZ, QUndoCommand* parent) :
  QUndoCommand(parent)
{
  _map = map;
  _mapSizeX = mapSizeX;
  _mapSizeZ = mapSizeZ;
  _mapSizeXOld = _map->GetSizeX() / 16;
  _mapSizeZOld = _map->GetSizeZ() / 16;
}

ChangeSizeCommand::~ChangeSizeCommand()
{
}

void ChangeSizeCommand::undo()
{
  //set old map
  deletedBlocks = _map->Resize(deletedBlocks, _mapSizeXOld, _mapSizeZOld);
}

void ChangeSizeCommand::redo()
{
  //set new map size
  deletedBlocks = _map->Resize(deletedBlocks, _mapSizeX, _mapSizeZ);
}