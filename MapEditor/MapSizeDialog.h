#pragma once
#include "qdialog.h"
#include <qlineedit.h>
#include <qspinbox.h>

class MapSizeDialog :
  public QDialog
{
  Q_OBJECT
public:
  MapSizeDialog(QWidget* parent = 0);
  ~MapSizeDialog();

  int GetSizeX() { return _spnBoxX->value(); }
  int GetSizeZ() { return _spnBoxZ->value(); }

private:
  QSpinBox* _spnBoxX;
  QSpinBox* _spnBoxZ;
};

