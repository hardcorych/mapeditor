#pragma once

#include <RemoveCommand.h>

RemoveCommand::RemoveCommand(osg::ref_ptr<Map> map,
                             int x,
                             int z, 
                             BlockType blockType, 
                             QUndoCommand* parent) :
    QUndoCommand(parent),
    _map(map),
    _x(x),
    _z(z),
    _blockType(blockType)
{
}

RemoveCommand::~RemoveCommand()
{
}

void RemoveCommand::undo()
{
  //add
  _map->AddBlock(_x, _z, _blockType);
}

void RemoveCommand::redo()
{
  //remove
  _map->RemoveBlock(_x, _z);
}