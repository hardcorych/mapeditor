#include "NewMapDialog.h"

#include <qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>

NewMapDialog::NewMapDialog(QWidget* parent) : QDialog(parent)
{
  QBoxLayout* layout = new QHBoxLayout(this);

  QLabel* labelX = new QLabel(this);
  QLabel* labelZ = new QLabel(this);

  labelX->setText("Size X (in blocks)");
  labelZ->setText("Size Z (in blocks)");

  _spnBoxX = new QSpinBox(this);
  _spnBoxZ = new QSpinBox(this);
  _spnBoxX->setMinimum(5);
  _spnBoxX->setMaximum(50);
  _spnBoxZ->setMinimum(5);
  _spnBoxZ->setMaximum(50);

  QPushButton* okBtn = new QPushButton(this);
  okBtn->setText("OK");
  connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);

  QPushButton* cancelBtn = new QPushButton(this);
  cancelBtn->setText("Cancel");
  connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

  layout->addWidget(labelX);
  layout->addWidget(_spnBoxX);
  layout->addWidget(labelZ);
  layout->addWidget(_spnBoxZ);
  layout->addWidget(okBtn);
  layout->addWidget(cancelBtn);

  setLayout(layout);
}

NewMapDialog::~NewMapDialog()
{
}
