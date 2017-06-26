/********************************************************************************
** Form generated from reading UI file 'MapEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEDITOR_H
#define UI_MAPEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditorClass
{
public:
    QWidget *centralWidget;
    QLabel *labelMessage;
    QGroupBox *groupBoxBlocks;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QLineEdit *lineEditBlockName;
    QLabel *labelBlockName;
    QLineEdit *lineEditBlockPath;
    QLabel *labelBlockPath;
    QCheckBox *checkBoxPassability;
    QCheckBox *checkBoxUnderTank;
    QPushButton *pushButtonPath;
    QPushButton *pushButtonCreateBlock;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QPushButton *pushButtonDeleteBlock;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MapEditorClass)
    {
        if (MapEditorClass->objectName().isEmpty())
            MapEditorClass->setObjectName(QStringLiteral("MapEditorClass"));
        MapEditorClass->resize(858, 492);
        centralWidget = new QWidget(MapEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelMessage = new QLabel(centralWidget);
        labelMessage->setObjectName(QStringLiteral("labelMessage"));
        labelMessage->setGeometry(QRect(10, 420, 191, 16));
        groupBoxBlocks = new QGroupBox(centralWidget);
        groupBoxBlocks->setObjectName(QStringLiteral("groupBoxBlocks"));
        groupBoxBlocks->setGeometry(QRect(10, 10, 531, 401));
        gridLayoutWidget = new QWidget(groupBoxBlocks);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 511, 371));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(550, 10, 291, 211));
        lineEditBlockName = new QLineEdit(groupBox);
        lineEditBlockName->setObjectName(QStringLiteral("lineEditBlockName"));
        lineEditBlockName->setGeometry(QRect(90, 20, 113, 20));
        labelBlockName = new QLabel(groupBox);
        labelBlockName->setObjectName(QStringLiteral("labelBlockName"));
        labelBlockName->setGeometry(QRect(10, 20, 61, 21));
        lineEditBlockPath = new QLineEdit(groupBox);
        lineEditBlockPath->setObjectName(QStringLiteral("lineEditBlockPath"));
        lineEditBlockPath->setGeometry(QRect(90, 50, 113, 20));
        labelBlockPath = new QLabel(groupBox);
        labelBlockPath->setObjectName(QStringLiteral("labelBlockPath"));
        labelBlockPath->setGeometry(QRect(10, 50, 71, 21));
        checkBoxPassability = new QCheckBox(groupBox);
        checkBoxPassability->setObjectName(QStringLiteral("checkBoxPassability"));
        checkBoxPassability->setGeometry(QRect(200, 110, 81, 17));
        checkBoxUnderTank = new QCheckBox(groupBox);
        checkBoxUnderTank->setObjectName(QStringLiteral("checkBoxUnderTank"));
        checkBoxUnderTank->setGeometry(QRect(200, 130, 91, 17));
        pushButtonPath = new QPushButton(groupBox);
        pushButtonPath->setObjectName(QStringLiteral("pushButtonPath"));
        pushButtonPath->setGeometry(QRect(210, 50, 75, 21));
        pushButtonCreateBlock = new QPushButton(groupBox);
        pushButtonCreateBlock->setObjectName(QStringLiteral("pushButtonCreateBlock"));
        pushButtonCreateBlock->setGeometry(QRect(20, 170, 111, 23));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(10, 90, 82, 17));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(10, 110, 82, 17));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(10, 130, 82, 17));
        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(100, 110, 82, 17));
        radioButton_5 = new QRadioButton(groupBox);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(100, 130, 82, 17));
        pushButtonDeleteBlock = new QPushButton(groupBox);
        pushButtonDeleteBlock->setObjectName(QStringLiteral("pushButtonDeleteBlock"));
        pushButtonDeleteBlock->setGeometry(QRect(160, 170, 111, 23));
        MapEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MapEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 858, 21));
        MapEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MapEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MapEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MapEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MapEditorClass->setStatusBar(statusBar);

        retranslateUi(MapEditorClass);

        QMetaObject::connectSlotsByName(MapEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *MapEditorClass)
    {
        MapEditorClass->setWindowTitle(QApplication::translate("MapEditorClass", "MapEditor", Q_NULLPTR));
        labelMessage->setText(QApplication::translate("MapEditorClass", "label", Q_NULLPTR));
        groupBoxBlocks->setTitle(QApplication::translate("MapEditorClass", "Blocks", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MapEditorClass", "Block editor", Q_NULLPTR));
        labelBlockName->setText(QApplication::translate("MapEditorClass", "Block name", Q_NULLPTR));
        labelBlockPath->setText(QApplication::translate("MapEditorClass", "Texture path", Q_NULLPTR));
        checkBoxPassability->setText(QApplication::translate("MapEditorClass", "Is passable", Q_NULLPTR));
        checkBoxUnderTank->setText(QApplication::translate("MapEditorClass", "Is under tank", Q_NULLPTR));
        pushButtonPath->setText(QApplication::translate("MapEditorClass", "Set path", Q_NULLPTR));
        pushButtonCreateBlock->setText(QApplication::translate("MapEditorClass", "Create block", Q_NULLPTR));
        radioButton->setText(QApplication::translate("MapEditorClass", "full", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("MapEditorClass", "left", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("MapEditorClass", "bottom", Q_NULLPTR));
        radioButton_4->setText(QApplication::translate("MapEditorClass", "right", Q_NULLPTR));
        radioButton_5->setText(QApplication::translate("MapEditorClass", "top", Q_NULLPTR));
        pushButtonDeleteBlock->setText(QApplication::translate("MapEditorClass", "Delete block", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MapEditorClass: public Ui_MapEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITOR_H
