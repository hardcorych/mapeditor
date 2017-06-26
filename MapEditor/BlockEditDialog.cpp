#include "BlockEditDialog.h"


BlockEditDialog::BlockEditDialog(QWidget* parent):
QDialog(parent)
{
  _lblBlockName = new QLabel(this);
  _lblTexPath = new QLabel(this);

  _lblBlockName->setText("Block name");
  _lblTexPath->setText("Texture path");

  _lineEditBlockName = new QLineEdit(this);
  _lineEditTexPath = new QLineEdit(this);

  _lineEditTexPath->setReadOnly(true);

  _pBtnSetTexPath = new QPushButton(this);
  
  _rBtnFillFull = new QRadioButton(this);
  _rBtnFillLeft = new QRadioButton(this);
  _rBtnFillRight = new QRadioButton(this);
  _rBtnFillBottom = new QRadioButton(this);
  _rBtnFillTop = new QRadioButton(this);

  _rBtnFillFull->setText("FULL");
  _rBtnFillLeft->setText("LEFT");
  _rBtnFillRight->setText("RIGHT");
  _rBtnFillBottom->setText("BOTTOM");
  _rBtnFillTop->setText("TOP");

  _chkBoxPassability = new QCheckBox(this);
  _chkBoxUnderTank = new QCheckBox(this);

  _pBtnCreateBlock = new QPushButton(this);
  _pBtnDeleteBlock = new QPushButton(this);
}


BlockEditDialog::~BlockEditDialog()
{
}
