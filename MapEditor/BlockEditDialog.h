#pragma once

#include <qdialog.h>

#include "BlockType.h"

class QButtonGroup;
class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;

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
  BlockEditDialog() = delete;
  BlockEditDialog(const BlockEditDialog&) = delete;
  BlockEditDialog(BlockType blockType, QWidget* parent = nullptr);
  ~BlockEditDialog() = default;

  BlockEditDialog& operator=(const BlockEditDialog&) = delete;
public:
  inline BlockType GetBlockType() const;
  
private:
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

