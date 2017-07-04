#pragma once

#include <qpainter.h>

#include <DrawBlockPixmap.h>

QPixmap DrawBlockPixmap(BlockType blockType)
{
  QPixmap pixmap(QSize(32, 32));
  QPixmap pixmapResult(QSize(32, 32));
  QPainter painter(&pixmapResult);

  pixmap.load(QString::fromStdString(blockType.GetTexPath()));
  int height = 16;
  int width = 16;

  std::string fillType = blockType.GetFillType();
  if (fillType == "FULL")
  {
    painter.drawPixmap(QRect(0, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(0, height, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, height, width, height), pixmap, pixmap.rect());
  }
  else if (fillType == "LEFT")
  {
    painter.drawPixmap(QRect(0, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(0, height, width, height), pixmap, pixmap.rect());
  }
  else if (fillType == "RIGHT")
  {
    painter.drawPixmap(QRect(width, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, height, width, height), pixmap, pixmap.rect());
  }
  else if (fillType == "BOTTOM")
  {
    painter.drawPixmap(QRect(0, height, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, height, width, height), pixmap, pixmap.rect());
  }
  else if (fillType == "TOP")
  {
    painter.drawPixmap(QRect(0, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, 0, width, height), pixmap, pixmap.rect());
  }

  return pixmapResult;
}