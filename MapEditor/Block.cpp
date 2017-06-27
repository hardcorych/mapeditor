#include "Block.h"


Block::Block()
{
}

//принимает координаты, тип блока
Block::Block(int x, int z, BlockType blockType) :
_x(x), _z(z),
_blockType(blockType)
{
  int tileSize = Tile::Size();

  createFromTiles(_blockType);

  if (_leftBottom != nullptr) addChild(_leftBottom);
  if (_leftTop != nullptr) addChild(_leftTop);
  if (_rightTop != nullptr) addChild(_rightTop);
  if (_rightBottom != nullptr) addChild(_rightBottom);
}

Block::~Block()
{
}

void Block::createFromTiles(BlockType blockType)
{
  int tileSize = Tile::Size();

  //blocktype parsing is here
  std::string typeName = blockType.GetTypeName();
  std::string texPath = blockType.GetTexPath();
  std::string fillType = blockType.GetFillType();

  if (typeName == "EMPTY")
  {
    _leftBottom = new Tile(_x, _z, typeName, EmptyTile::LEFT_BOTTOM);
    _leftTop = new Tile(_x, _z + tileSize, typeName, EmptyTile::LEFT_TOP);
    _rightTop = new Tile(_x + tileSize, _z + tileSize,
      typeName, EmptyTile::RIGHT_TOP);
    _rightBottom = new Tile(_x + tileSize, _z, typeName, EmptyTile::RIGHT_BOTTOM);
  }
  else
  {
    if (fillType == "FULL")
    {
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, typeName, texPath);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
    }
    else if (fillType == "BOTTOM")
    {
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, "EMPTY", EmptyTile::LEFT_TOP);
      _rightTop = new Tile(_x + tileSize, _z + tileSize,
        "EMPTY", EmptyTile::RIGHT_TOP);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
    }
    else if (fillType == "LEFT")
    {
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, typeName, texPath);
      _rightTop = new Tile(_x + tileSize, _z + tileSize,
        "EMPTY", EmptyTile::RIGHT_TOP);
      _rightBottom = new Tile(_x + tileSize, _z,
        "EMPTY", EmptyTile::RIGHT_BOTTOM);
    }
    else if (fillType == "RIGHT")
    {
      _leftBottom = new Tile(_x, _z, "EMPTY", EmptyTile::LEFT_BOTTOM);
      _leftTop = new Tile(_x, _z + tileSize, "EMPTY", EmptyTile::LEFT_TOP);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
    }
    else if (fillType == "TOP")
    {
      _leftBottom = new Tile(_x, _z, "EMPTY", EmptyTile::LEFT_BOTTOM);
      _leftTop = new Tile(_x, _z + tileSize, typeName, texPath);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, _z,
        "EMPTY", EmptyTile::RIGHT_BOTTOM);
    }
  }
}

void Block::SetType(BlockType blockType)
{
  std::string typeName = blockType.GetTypeName();
  std::string texPath = blockType.GetTexPath();
  //FillType fillType = blockType.GetFillType();
  std::string fillType = blockType.GetFillType();

  if (_blockType != blockType)        //если блок точно такой же, ничего не меняется
  {													//иначе происходит замена
    osg::ref_ptr<Tile> oldLeftBottom = _leftBottom;
    osg::ref_ptr<Tile> oldLeftTop = _leftTop;
    osg::ref_ptr<Tile> oldRightTop = _rightTop;
    osg::ref_ptr<Tile> oldRightBottom = _rightBottom;

    //замена блока
    _blockType = blockType;

    createFromTiles(_blockType);

    replaceChild(oldLeftBottom, _leftBottom);
    replaceChild(oldLeftTop, _leftTop);
    replaceChild(oldRightTop, _rightTop);
    replaceChild(oldRightBottom, _rightBottom);
  }
}

//переделать тип возвращаемой функции
std::pair<QString, QString> Block::GetType_str()
{
  //QString texType;
  QString fillType = QString::fromStdString(_blockType.GetFillType());
  
  //проверка на empty?
  /*
  switch (_type)
  {
  case TexType::ARMOR:
    texType = "ARMOR";
    break;
  case TexType::BORDER:
    texType = "BORDER";
    break;
  case TexType::BRICK:
    texType = "BRICK";
    break;
  case TexType::BUSHES:
    texType = "BUSHES";
    break;
  case TexType::EMPTY:
    //не писать в файл
    return std::make_pair("EMPTY", "EMPTY");
  case TexType::WATER:
    texType = "WATER";
    break;
  case TexType::ICE:
    texType = "ICE";
    break;
  }
  */
  /*
  switch (_blockType.GetFillType())
  {
  case FillType::BOTTOM:
    fillType = "BOTTOM";
    break;
  case FillType::FULL:
    fillType = "FULL";
    break;
  case FillType::LEFT:
    fillType = "LEFT";
    break;
  case FillType::RIGHT:
    fillType = "RIGHT";
    break;
  case FillType::TOP:
    fillType = "TOP";
    break;
  }
  */
  //return std::make_pair(texType, fillType);
  return std::make_pair("izi", fillType);
}
