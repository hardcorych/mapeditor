#pragma once
#include <MapSizeDialog.h>

#include <qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>

MapSizeDialog::MapSizeDialog(QWidget* parent) : 
  QDialog(parent)
{
  QGridLayout* layout = new QGridLayout(this);

  QLabel* labelX = new QLabel(this);
  QLabel* labelZ = new QLabel(this);

  labelX->setText("Size X (in blocks)");
  labelZ->setText("Size Z (in blocks)");

  _spnBoxX = new QSpinBox(this);
  _spnBoxZ = new QSpinBox(this);
  _spnBoxX->setMinimum(5);
  _spnBoxX->setMaximum(30);
  _spnBoxZ->setMinimum(5);
  _spnBoxZ->setMaximum(30);

  QPushButton* okBtn = new QPushButton(this);
  okBtn->setText("OK");
  connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);

  QPushButton* cancelBtn = new QPushButton(this);
  cancelBtn->setText("Cancel");
  connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

  layout->addWidget(labelX, 0, 0);
  layout->addWidget(_spnBoxX, 1, 0);
  layout->addWidget(labelZ, 0, 1);
  layout->addWidget(_spnBoxZ, 1, 1);
  layout->addWidget(okBtn, 2, 0);
  layout->addWidget(cancelBtn, 2, 1);

  setLayout(layout);
}
