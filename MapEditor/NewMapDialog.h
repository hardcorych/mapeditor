#pragma once
#include "qdialog.h"
#include <qlineedit.h>
#include <qspinbox.h>

class NewMapDialog :
  public QDialog
{
  Q_OBJECT
public:
  NewMapDialog(QWidget* parent = 0);
  ~NewMapDialog();

  int GetSizeX() { return _spnBoxX->value(); }
  int GetSizeZ() { return _spnBoxZ->value(); }

private:
  QSpinBox* _spnBoxX;
  QSpinBox* _spnBoxZ;
};

