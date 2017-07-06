#pragma once
#include "qdialog.h"
#include <qlineedit.h>
#include <qspinbox.h>

class MapSizeDialog : public QDialog
{
  Q_OBJECT
public:
  MapSizeDialog(QWidget* parent = nullptr);
  ~MapSizeDialog();

public:
  inline int GetSizeX() const;
  inline int GetSizeZ() const;

private:
  QSpinBox* _spnBoxX;
  QSpinBox* _spnBoxZ;
};

inline int MapSizeDialog::GetSizeX() const 
{ 
  return _spnBoxX->value(); 
}

inline int MapSizeDialog::GetSizeZ() const
{ 
  return _spnBoxZ->value();
}


