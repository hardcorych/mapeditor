#pragma once

#include <qradiobutton.h>

#include <Block.h>

class QBlockRadioButton : public QRadioButton
{
  Q_OBJECT
public:
  explicit QBlockRadioButton(QWidget *parent = 0);
  ~QBlockRadioButton();

  std::string GetType() { return _typeName; }
  FillType GetFillType() { return _fillType; }

  public slots:

private:
  std::string _typeName;
  std::string _texPath;
  FillType _fillType;
};

