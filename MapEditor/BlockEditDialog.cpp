#pragma once
#include "BlockEditDialog.h"

#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qdialog.h>
#include <qfiledialog.h>
#include <qgridlayout.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qradiobutton.h>

BlockEditDialog::BlockEditDialog(BlockType blockType,
                                 QWidget* parent) :
    QDialog(parent),
    _blockType(blockType)
{
  setWindowTitle("BlockEditor");

  _lblBlockName = new QLabel(this);
  _lblTexPath = new QLabel(this);
  
  _lblBlockName->setText("Block name");
  _lblTexPath->setText("Texture path");

  _lineEditBlockName = new QLineEdit(this);
  _lineEditTexPath = new QLineEdit(this);

  _lineEditBlockName->
    setText(QString::fromStdString(_blockType.GetTypeName()));

  _lineEditTexPath->setReadOnly(true);
  _lineEditTexPath->
    setText(QString::fromStdString(_blockType.GetTexPath()));

  _pBtnSetTexPath = new QPushButton(this);

  _pBtnSetTexPath->setText("Set path");
  
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

  if (_blockType.isFillFull())
  {
    _rBtnFillFull->setChecked(true);
  }
  else if (_blockType.isFillLeft())
  {
    _rBtnFillLeft->setChecked(true);
  }
  else if (_blockType.isFillRight())
  {
    _rBtnFillRight->setChecked(true);
  }
  else if (_blockType.isFillBottom())
  {
    _rBtnFillBottom->setChecked(true);
  }
  else if (_blockType.isFillTop())
  {
    _rBtnFillTop->setChecked(true);
  }

  _chkBoxPassability = new QCheckBox(this);
  _chkBoxUnderTank = new QCheckBox(this);

  _chkBoxPassability->setText("Is passable");
  _chkBoxUnderTank->setText("Is under tank");

  _chkBoxPassability->setChecked(_blockType.GetPassability());
  _chkBoxUnderTank->setChecked(_blockType.GetUnderTank());

  _pBtnCreateBlockType = new QPushButton(this);
  _pBtnChangeBlockType = new QPushButton(this);
  _pBtnDeleteBlockType = new QPushButton(this);
  _pBtnCancel = new QPushButton(this);

  _pBtnCreateBlockType->setText("Create block");
  _pBtnChangeBlockType->setText("Change block");
  _pBtnDeleteBlockType->setText("Delete block");
  _pBtnCancel->setText("Cancel");

  QGridLayout* layout = new QGridLayout(this);

  layout->addWidget(_lblBlockName, 0, 0);
  layout->addWidget(_lineEditBlockName, 0, 1);

  layout->addWidget(_lblTexPath, 1, 0);
  layout->addWidget(_lineEditTexPath, 1, 1);
  layout->addWidget(_pBtnSetTexPath, 1, 2);

  _groupBoxFill = new QGroupBox(this);
  QHBoxLayout *groupBoxLayout = new QHBoxLayout(this);

  _groupBoxFill->setLayout(groupBoxLayout);
  _groupBoxFill->setTitle("Fill");
  
  groupBoxLayout->addWidget(_rBtnFillFull);
  groupBoxLayout->addWidget(_rBtnFillLeft);
  groupBoxLayout->addWidget(_rBtnFillRight);
  groupBoxLayout->addWidget(_rBtnFillBottom);
  groupBoxLayout->addWidget(_rBtnFillTop);

  _btnGroupFill = new QButtonGroup(this);
  _btnGroupFill->addButton(_rBtnFillFull);
  _btnGroupFill->addButton(_rBtnFillLeft);
  _btnGroupFill->addButton(_rBtnFillRight);
  _btnGroupFill->addButton(_rBtnFillBottom);
  _btnGroupFill->addButton(_rBtnFillTop);

  layout->addWidget(_groupBoxFill, 2, 1);

  layout->addWidget(_chkBoxPassability, 3, 1);
  layout->addWidget(_chkBoxUnderTank, 3, 2);

  layout->addWidget(_pBtnCreateBlockType, 4, 0);
  layout->addWidget(_pBtnChangeBlockType, 4, 1);
  layout->addWidget(_pBtnDeleteBlockType, 4, 2);
  layout->addWidget(_pBtnCancel, 4, 3);

  connect(_pBtnSetTexPath, 
          &QPushButton::clicked,
          this, 
          &BlockEditDialog::setTexPath);
  connect(_pBtnCreateBlockType, 
          &QPushButton::clicked,
          this,
          &BlockEditDialog::createBlockType);
  connect(_pBtnChangeBlockType, 
          &QPushButton::clicked,
          this,
          &BlockEditDialog::changeBlockType);
  connect(_pBtnDeleteBlockType, 
          &QPushButton::clicked,
          this, 
          &BlockEditDialog::deleteBlockType);

  connect(_pBtnCancel,
          &QPushButton::clicked,
          this, 
          &QDialog::reject);
}

void BlockEditDialog::setTexPath()
{
  QString filename = QFileDialog::getOpenFileName(this, 
                                                  tr("Open texture"), 
                                                  ".",
                                                  tr("PNG and JPG files (*.png *.jpg)"));

  QFile file(filename);

  if (!filename.isEmpty())
  {
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
      QMessageBox::warning(this, "file error", "file can't be opened", QMessageBox::Ok);
    }
    else
    {
      _lineEditTexPath->setText(filename);
    }
  }

}

void BlockEditDialog::createBlockType()
{
  QString errorText;
  if (_lineEditBlockName->text().isEmpty())
  {
    errorText = "Empty name";
  }
  else if (_lineEditTexPath->text().isEmpty())
  {
    errorText = "Empty texture path";
  }
  else if (_btnGroupFill->checkedButton() == 0)
  {
    errorText = "Fill type is not selected";
  }

  if (!errorText.isEmpty())
  {
    QMessageBox::critical(this, "Error", errorText, QMessageBox::Ok);
  }
  else 
  {
    _blockType.SetTypeName(_lineEditBlockName->text().toStdString());
    _blockType.SetTexPath(_lineEditTexPath->text().toStdString());
    _blockType.SetFillType(_btnGroupFill->checkedButton()->text().toStdString());
    _blockType.SetPassability(_chkBoxPassability->isChecked());
    _blockType.SetUnderTank(_chkBoxUnderTank->isChecked());
    emit QDialog::done(BlockEditAction::CREATE);
  }
}

void BlockEditDialog::changeBlockType()
{
  QString errorText;
  if (_lineEditBlockName->text().isEmpty())
  {
    errorText = "Empty name";
  }
  else if (_lineEditTexPath->text().isEmpty())
  {
    errorText = "Empty texture path";
  }
  else if (_btnGroupFill->checkedButton() == 0)
  {
    errorText = "Fill type is not selected";
  }

  if (!errorText.isEmpty())
  {
    QMessageBox::critical(this, "Error", errorText, QMessageBox::Ok);
  }
  else
  {
    _blockType.SetTypeName(_lineEditBlockName->text().toStdString());
    _blockType.SetTexPath(_lineEditTexPath->text().toStdString());
    _blockType.SetFillType(_btnGroupFill->checkedButton()->text().toStdString());
    _blockType.SetPassability(_chkBoxPassability->isChecked());
    _blockType.SetUnderTank(_chkBoxUnderTank->isChecked());
    emit QDialog::done(BlockEditAction::CHANGE);
  }
}

void BlockEditDialog::deleteBlockType()
{
  emit QDialog::done(BlockEditAction::DELETE);
}
