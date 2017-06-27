// undo/redo commands
#pragma once
#include <mutex>

#include <qundostack.h>

#include <Block.h>
#include <Map.h>

//map editor
class AddCommand : public QUndoCommand	//add block on map
{
public:
  AddCommand(osg::ref_ptr<Block> block, BlockType blockType,
    QUndoCommand* parent = 0);
  ~AddCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Block> _block = nullptr;
  BlockType _blockType;
};

class ReplaceCommand : public QUndoCommand	//replace existing block on map
{
public:
  ReplaceCommand(osg::ref_ptr<Block> block,
   BlockType blockType, QUndoCommand* parent = 0);
  ~ReplaceCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Block> _block = nullptr;
  BlockType _blockType;
  BlockType _blockTypeOld;
};

class RemoveCommand : public QUndoCommand	//remove block from map
{
public:
  RemoveCommand(osg::ref_ptr<Block> block, QUndoCommand* parent = 0);
  ~RemoveCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Block> _block = nullptr;
  BlockType _blockType;
};

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

//block editor
class CreateBlockTypeCommand : public QUndoCommand	
{
public:
  CreateBlockTypeCommand(BlockType blockType, QUndoCommand* parent = 0);
  ~CreateBlockTypeCommand();

  void undo() override;
  void redo() override;

private:
  BlockType _blockType;
};

class ChangeBlockTypeCommand : public QUndoCommand	
{
public:
  ChangeBlockTypeCommand(QUndoCommand* parent = 0);
  ~ChangeBlockTypeCommand();

  void undo() override;
  void redo() override;

private:

};

class DeleteBlockTypeCommand : public QUndoCommand	
{
public:
  DeleteBlockTypeCommand(QUndoCommand* parent = 0);
  ~DeleteBlockTypeCommand();

  void undo() override;
  void redo() override;

private:

};