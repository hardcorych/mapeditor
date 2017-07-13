#pragma once
#include <DrawBlockPixmap.h>

#include <qpainter.h>
#include <qpixmap.h>

#include <BlockType.h>

QPixmap DrawBlockPixmap(const BlockType& blockType)
{
  QPixmap pixmap(QSize(32, 32));
  QPixmap pixmapResult(QSize(32, 32));
  QPainter painter(&pixmapResult);

  pixmap.load(QString::fromStdString(blockType.GetTexPath()));
  int height = 16;
  int width = 16;

  if (blockType.isFillFull())
  {
    painter.drawPixmap(QRect(0, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(0, height, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, height, width, height), pixmap, pixmap.rect());
  }
  else if (blockType.isFillLeft())
  {
    painter.drawPixmap(QRect(0, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(0, height, width, height), pixmap, pixmap.rect());
  }
  else if (blockType.isFillRight())
  {
    painter.drawPixmap(QRect(width, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, height, width, height), pixmap, pixmap.rect());
  }
  else if (blockType.isFillBottom())
  {
    painter.drawPixmap(QRect(0, height, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, height, width, height), pixmap, pixmap.rect());
  }
  else if (blockType.isFillTop())
  {
    painter.drawPixmap(QRect(0, 0, width, height), pixmap, pixmap.rect());
    painter.drawPixmap(QRect(width, 0, width, height), pixmap, pixmap.rect());
  }

  return pixmapResult;
}