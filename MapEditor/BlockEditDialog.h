#pragma once

#include <qcheckbox.h>
#include <qdialog.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>

#include <BlockType.h>

enum class BlockEditAction
{
  CREATE = 2,
  CHANGE = 3,
  DELETE = 4
};

class BlockEditDialog: public QDialog
{
  Q_OBJECT
public:
  BlockEditDialog(QWidget* parent, BlockType blockType);
  ~BlockEditDialog();

  BlockType GetBlockType() const { return _blockType; }
  
private:
  BlockType _blockType;

  QLabel* _lblBlockName;
  QLabel* _lblTexPath;

  QLineEdit* _lineEditBlockName;
  QLineEdit* _lineEditTexPath;

  QPushButton* _pBtnSetTexPath;

  QGroupBox* _groupBoxFill;
  QRadioButton* _rBtnFillFull;
  QRadioButton* _rBtnFillLeft;
  QRadioButton* _rBtnFillRight;
  QRadioButton* _rBtnFillBottom;
  QRadioButton* _rBtnFillTop;

  QCheckBox* _chkBoxPassability;
  QCheckBox* _chkBoxUnderTank;

  QPushButton* _pBtnCreateBlockType;
  QPushButton* _pBtnChangeBlockType;
  QPushButton* _pBtnDeleteBlockType;
  QPushButton* _pBtnCancel;

  private slots:
  void setTexPath();
};

