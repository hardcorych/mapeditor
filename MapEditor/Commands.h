// undo/redo commands
#pragma once
#include <mutex>

#include <qundostack.h>

#include <Block.h>
#include <Map.h>
#include <MapEditor.h>

class AddCommand : public QUndoCommand	//команда добавления блока на карту
{
public:
  AddCommand(osg::ref_ptr<Block> block, TexType type, FillType fType, QUndoCommand* parent = 0);
  ~AddCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Block> _block = nullptr;
  TexType _type;
  FillType _fType;
};

class ReplaceCommand : public QUndoCommand	//команда замены существующего блока
{
public:
  ReplaceCommand(osg::ref_ptr<Block> block, TexType type, FillType fType, QUndoCommand* parent = 0);
  ~ReplaceCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Block> _block = nullptr;
  TexType _type;
  TexType _typeOld;
  FillType _fType;
  FillType _fTypeOld;
};

class RemoveCommand : public QUndoCommand	//команда удаления блока с карты
{
public:
  RemoveCommand(osg::ref_ptr<Block> block, QUndoCommand* parent = 0);
  ~RemoveCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Block> _block = nullptr;
  TexType _type;
  FillType _fType;
};

class ChangeSizeCommand : public QUndoCommand	//команда смены размера карты
{
public:
  ChangeSizeCommand(osg::ref_ptr<Map> map, int mapSizeX, int mapSizeZ, QUndoCommand* parent = 0);
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