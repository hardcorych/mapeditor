#pragma once

#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qdialog.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>

#include <BlockType.h>

class BlockEditDialog: public QDialog
{
  Q_OBJECT
public:
  enum BlockEditAction
  {
    CREATE = 2,
    CHANGE = 3,
    DELETE = 4
  };

public:
  BlockEditDialog(BlockType blockType, QWidget* parent = nullptr);
  ~BlockEditDialog();

public:
  inline BlockType GetBlockType() const;
  
private slots:
  void setTexPath();
  void createBlockType();
  void changeBlockType();
  void deleteBlockType();

private:
  BlockType _blockType;

  QLabel* _lblBlockName;
  QLabel* _lblTexPath;

  QLineEdit* _lineEditBlockName;
  QLineEdit* _lineEditTexPath;

  QPushButton* _pBtnSetTexPath;

  QGroupBox* _groupBoxFill;
  QButtonGroup* _btnGroupFill;
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
};

inline BlockType BlockEditDialog::GetBlockType() const 
{ 
  return _blockType; 
}

