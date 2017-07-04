#pragma once

#include <qbuttongroup.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qwidget.h>

#include <BlockType.h>

class TableTexPathsWidget : public QWidget
{
  Q_OBJECT
public:
  TableTexPathsWidget(std::map<int, BlockType> blockTypes,
    QButtonGroup* btnGroupBlocks, QWidget* parent = 0);
  ~TableTexPathsWidget();

private:
  QTableWidget* _tableWidget;
  int _rowCounter;
};

