#pragma once

#include <qlistwidget.h>
#include <qwidget.h>

class ListTexPathsWidget : public QWidget
{
  Q_OBJECT
public:
  ListTexPathsWidget(QWidget* parent = 0);
  ~ListTexPathsWidget();

private:
  QListWidget* _listWidget;
};

