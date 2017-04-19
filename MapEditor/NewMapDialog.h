#pragma once
#include "qdialog.h"
#include <qlineedit.h>

class NewMapDialog :
	public QDialog
{
	Q_OBJECT
public:
	NewMapDialog(QWidget* parent = 0);
	~NewMapDialog();

signals:
	void applied();

private:
	QLineEdit* _editX;
	QLineEdit* _editZ;
};

