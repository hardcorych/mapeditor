// undo/redo commands
#pragma once
#include <memory>
#include <mutex>

#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qundostack.h>

#include <Block.h>
#include <Map.h>
#include <MapEditor.h>

QPixmap DrawBlockPixmap(BlockType blockType);

//map editor
class AddCommand : public QUndoCommand	//add block on map
{
public:
  AddCommand(osg::ref_ptr<Map> map, int x, int z,
    BlockType blockType,
    QUndoCommand* parent = 0);
  ~AddCommand();

  void undo() override;
  void redo() override;

private:
  //osg::ref_ptr<Block> _block = nullptr;
  osg::ref_ptr<Map> _map;
  int _x;
  int _z;
  BlockType _blockType;
};

class ReplaceCommand : public QUndoCommand	//replace existing block on map
{
public:
  ReplaceCommand(osg::ref_ptr<Map> map, 
                 osg::ref_ptr<Block> block, 
                 BlockType blockType, 
                 QUndoCommand* parent = 0);
  ~ReplaceCommand();

  void undo() override;
  void redo() override;

private:
  //osg::ref_ptr<Block> _block = nullptr;
  osg::ref_ptr<Map> _map = nullptr;
  BlockType _blockType;
  BlockType _blockTypeOld;
  int _x;
  int _z;
};

class RemoveCommand : public QUndoCommand	//remove block from map
{
public:
  RemoveCommand(osg::ref_ptr<Map> map,
    int x, int z, BlockType blockType, QUndoCommand* parent = 0);
  ~RemoveCommand();

  void undo() override;
  void redo() override;

private:
  osg::ref_ptr<Map> _map;
  //osg::ref_ptr<Block> _block = nullptr;
  int _x;
  int _z;
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
  CreateBlockTypeCommand(QButtonGroup* btnGroup, 
    BlockType blockType, MapEditor* mapEditor, QUndoCommand* parent = 0);
  ~CreateBlockTypeCommand();

  void undo() override;
  void redo() override;

private:
  BlockType _blockType;
  MapEditor* _mapEditor;
  QRadioButton* _button;
  QButtonGroup* _btnGroup;
  int _row;
  int _col;
};

class ChangeBlockTypeCommand : public QUndoCommand	
{
public:
  ChangeBlockTypeCommand(QAbstractButton* button,
    BlockType& blockType, BlockType blockTypeNew,
  MapEditor* mapEditor, QUndoCommand* parent = 0);
  ~ChangeBlockTypeCommand();

  void undo() override;
  void redo() override;

private:
  BlockType& _blockTypeRef;
  BlockType _blockType;
  BlockType _blockTypeNew;
  QAbstractButton* _button;
  MapEditor* _mapEditor;
};

class DeleteBlockTypeCommand : public QUndoCommand	
{
public:
  DeleteBlockTypeCommand(QButtonGroup* btnGroup, BlockType blockType,
    MapEditor* mapEditor, QUndoCommand* parent = 0);
  ~DeleteBlockTypeCommand();

  void undo() override;
  void redo() override;

private:
  BlockType _blockType;
  MapEditor* _mapEditor;
  QRadioButton* _button;
  int _buttonId;
  QButtonGroup* _btnGroup;
  int _row;
  int _col;
};