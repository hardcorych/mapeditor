#pragma once

#include <qcheckbox.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>

class BlockEditDialog: public QDialog
{
  Q_OBJECT
public:
  BlockEditDialog(QWidget* parent = 0);
  ~BlockEditDialog();

private:
  QLabel* _lblBlockName;
  QLabel* _lblTexPath;

  QLineEdit* _lineEditBlockName;
  QLineEdit* _lineEditTexPath;

  QPushButton* _pBtnSetTexPath;

  QRadioButton* _rBtnFillFull;
  QRadioButton* _rBtnFillLeft;
  QRadioButton* _rBtnFillRight;
  QRadioButton* _rBtnFillBottom;
  QRadioButton* _rBtnFillTop;

  QCheckBox* _chkBoxPassability;
  QCheckBox* _chkBoxUnderTank;

  QPushButton* _pBtnCreateBlock;
  QPushButton* _pBtnDeleteBlock;
};

