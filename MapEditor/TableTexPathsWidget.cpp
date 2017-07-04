#include "TableTexPathsWidget.h"


TableTexPathsWidget::TableTexPathsWidget(std::map<int, BlockType> blockTypes,
  QButtonGroup* btnGroupBlock,
  QWidget* parent) :
  QWidget(parent),
  _rowCounter(0)
{
  _tableWidget = new QTableWidget(this);
  _tableWidget->setColumnCount(3);
  QStringList tableHeader;
  tableHeader << "id" << "name" << "tex path";
  _tableWidget->setHorizontalHeaderLabels(tableHeader);
  _tableWidget->resize(500, 500);

  //adding the items  
  QList<QAbstractButton*> buttons = btnGroupBlock->buttons();

  for (QList<QAbstractButton*>::iterator it = buttons.begin();
    it != buttons.end(); ++it)
  {
    int blockTypeId = btnGroupBlock->id(*it);

    QString blockTypeIdStr = QString::number(blockTypeId);

    QString blockTypeName =
      QString::fromStdString(blockTypes[blockTypeId].GetTypeName()) +
      "_" +
      QString::fromStdString(blockTypes[blockTypeId].GetFillType());

    QString blockTypeTexPath =
      QString::fromStdString(blockTypes[blockTypeId].GetTexPath());

    _tableWidget->insertRow(_rowCounter);
    _tableWidget->setItem(_rowCounter, 0, 
      new QTableWidgetItem(blockTypeIdStr));
    _tableWidget->setItem(_rowCounter, 1,
      new QTableWidgetItem(blockTypeName));
    _tableWidget->setItem(_rowCounter, 2,
      new QTableWidgetItem(blockTypeTexPath));
    _rowCounter++;
  }
  _tableWidget->resizeColumnsToContents();
}


TableTexPathsWidget::~TableTexPathsWidget()
{

}
