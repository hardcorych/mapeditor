#pragma once

#include <qpainter.h>

#include <BlockType.h>
#include <CreateBlockTypeCommand.h>
#include <CreateBlockTypeEvent.h>
#include <DeleteBlockTypeEvent.h>
#include <DrawBlockPixmap.h>
#include <MapEditor.h>

CreateBlockTypeCommand::CreateBlockTypeCommand(const BlockType& blockType, 
                                               MapEditor& mapEditor, 
                                               QUndoCommand* parent) :
    QUndoCommand(parent),
    _blockType(blockType),
    _mapEditor(mapEditor),
    _blockTypeId(0)
{
}

CreateBlockTypeCommand::~CreateBlockTypeCommand()
{
}

void CreateBlockTypeCommand::undo()
{
  _mapEditor.DeleteBlockType(_blockTypeId);
  QCoreApplication::postEvent(&_mapEditor,
                              new DeleteBlockTypeEvent(_blockTypeId));
}

void CreateBlockTypeCommand::redo()
{
  _blockTypeId = _mapEditor.AddBlockType(_blockType);
  QCoreApplication::postEvent(&_mapEditor, 
                              new CreateBlockTypeEvent(_blockType));
}