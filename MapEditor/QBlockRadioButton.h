#pragma once

#include <qradiobutton.h>

#include <BlockType.h>

//убрать?
class QBlockRadioButton : public QRadioButton
{
  Q_OBJECT
public:
  explicit QBlockRadioButton(QWidget *parent = 0);
  ~QBlockRadioButton();

  public slots:

private:
  BlockType _blockType;
};
