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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditorClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QRadioButton *radioBtnBushes;
    QRadioButton *radioBtnWater;
    QRadioButton *radioBtnIce;
    QRadioButton *radioBtnArmorFull;
    QRadioButton *radioBtnArmorLeft;
    QRadioButton *radioBtnArmorRight;
    QRadioButton *radioBtnArmorTop;
    QRadioButton *radioBtnArmorBottom;
    QRadioButton *radioBtnBrickFull;
    QRadioButton *radioBtnBrickTop;
    QRadioButton *radioBtnBrickLeft;
    QRadioButton *radioBtnBrickRight;
    QRadioButton *radioBtnBrickBottom;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MapEditorClass)
    {
        if (MapEditorClass->objectName().isEmpty())
            MapEditorClass->setObjectName(QStringLiteral("MapEditorClass"));
        MapEditorClass->resize(533, 430);
        centralWidget = new QWidget(MapEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 511, 371));
        radioBtnBushes = new QRadioButton(groupBox);
        radioBtnBushes->setObjectName(QStringLiteral("radioBtnBushes"));
        radioBtnBushes->setGeometry(QRect(20, 10, 91, 81));
        radioBtnBushes->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/blocks/bushes.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnBushes->setIcon(icon);
        radioBtnBushes->setIconSize(QSize(64, 64));
        radioBtnWater = new QRadioButton(groupBox);
        radioBtnWater->setObjectName(QStringLiteral("radioBtnWater"));
        radioBtnWater->setGeometry(QRect(210, 10, 91, 81));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Resources/blocks/water.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnWater->setIcon(icon1);
        radioBtnWater->setIconSize(QSize(64, 64));
        radioBtnIce = new QRadioButton(groupBox);
        radioBtnIce->setObjectName(QStringLiteral("radioBtnIce"));
        radioBtnIce->setGeometry(QRect(390, 10, 91, 81));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Resources/blocks/ice.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnIce->setIcon(icon2);
        radioBtnIce->setIconSize(QSize(64, 64));
        radioBtnArmorFull = new QRadioButton(groupBox);
        radioBtnArmorFull->setObjectName(QStringLiteral("radioBtnArmorFull"));
        radioBtnArmorFull->setGeometry(QRect(330, 110, 91, 81));
        QIcon icon3;
        icon3.addFile(QStringLiteral("Resources/blocks/armor_full.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnArmorFull->setIcon(icon3);
        radioBtnArmorFull->setIconSize(QSize(64, 64));
        radioBtnArmorLeft = new QRadioButton(groupBox);
        radioBtnArmorLeft->setObjectName(QStringLiteral("radioBtnArmorLeft"));
        radioBtnArmorLeft->setGeometry(QRect(270, 190, 91, 81));
        QIcon icon4;
        icon4.addFile(QStringLiteral("Resources/blocks/armor_left.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnArmorLeft->setIcon(icon4);
        radioBtnArmorLeft->setIconSize(QSize(64, 64));
        radioBtnArmorRight = new QRadioButton(groupBox);
        radioBtnArmorRight->setObjectName(QStringLiteral("radioBtnArmorRight"));
        radioBtnArmorRight->setGeometry(QRect(390, 190, 91, 81));
        QIcon icon5;
        icon5.addFile(QStringLiteral("Resources/blocks/armor_right.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnArmorRight->setIcon(icon5);
        radioBtnArmorRight->setIconSize(QSize(64, 64));
        radioBtnArmorTop = new QRadioButton(groupBox);
        radioBtnArmorTop->setObjectName(QStringLiteral("radioBtnArmorTop"));
        radioBtnArmorTop->setGeometry(QRect(390, 270, 91, 81));
        QIcon icon6;
        icon6.addFile(QStringLiteral("Resources/blocks/armor_top.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnArmorTop->setIcon(icon6);
        radioBtnArmorTop->setIconSize(QSize(64, 64));
        radioBtnArmorBottom = new QRadioButton(groupBox);
        radioBtnArmorBottom->setObjectName(QStringLiteral("radioBtnArmorBottom"));
        radioBtnArmorBottom->setGeometry(QRect(270, 270, 91, 81));
        QIcon icon7;
        icon7.addFile(QStringLiteral("Resources/blocks/armor_bottom.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnArmorBottom->setIcon(icon7);
        radioBtnArmorBottom->setIconSize(QSize(64, 64));
        radioBtnBrickFull = new QRadioButton(groupBox);
        radioBtnBrickFull->setObjectName(QStringLiteral("radioBtnBrickFull"));
        radioBtnBrickFull->setGeometry(QRect(80, 110, 91, 81));
        QIcon icon8;
        icon8.addFile(QStringLiteral("Resources/blocks/brick_full.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnBrickFull->setIcon(icon8);
        radioBtnBrickFull->setIconSize(QSize(64, 64));
        radioBtnBrickTop = new QRadioButton(groupBox);
        radioBtnBrickTop->setObjectName(QStringLiteral("radioBtnBrickTop"));
        radioBtnBrickTop->setGeometry(QRect(140, 270, 91, 81));
        QIcon icon9;
        icon9.addFile(QStringLiteral("Resources/blocks/brick_top.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnBrickTop->setIcon(icon9);
        radioBtnBrickTop->setIconSize(QSize(64, 64));
        radioBtnBrickLeft = new QRadioButton(groupBox);
        radioBtnBrickLeft->setObjectName(QStringLiteral("radioBtnBrickLeft"));
        radioBtnBrickLeft->setGeometry(QRect(20, 190, 91, 81));
        QIcon icon10;
        icon10.addFile(QStringLiteral("Resources/blocks/brick_left.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnBrickLeft->setIcon(icon10);
        radioBtnBrickLeft->setIconSize(QSize(64, 64));
        radioBtnBrickRight = new QRadioButton(groupBox);
        radioBtnBrickRight->setObjectName(QStringLiteral("radioBtnBrickRight"));
        radioBtnBrickRight->setGeometry(QRect(140, 190, 91, 81));
        QIcon icon11;
        icon11.addFile(QStringLiteral("Resources/blocks/brick_right.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnBrickRight->setIcon(icon11);
        radioBtnBrickRight->setIconSize(QSize(64, 64));
        radioBtnBrickBottom = new QRadioButton(groupBox);
        radioBtnBrickBottom->setObjectName(QStringLiteral("radioBtnBrickBottom"));
        radioBtnBrickBottom->setGeometry(QRect(20, 270, 91, 81));
        QIcon icon12;
        icon12.addFile(QStringLiteral("Resources/blocks/brick_bottom.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnBrickBottom->setIcon(icon12);
        radioBtnBrickBottom->setIconSize(QSize(64, 64));
        MapEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MapEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 533, 21));
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
        groupBox->setTitle(QApplication::translate("MapEditorClass", "Blocks", Q_NULLPTR));
        radioBtnBushes->setText(QString());
        radioBtnBushes->setShortcut(QString());
        radioBtnWater->setText(QString());
        radioBtnIce->setText(QString());
        radioBtnArmorFull->setText(QString());
        radioBtnArmorLeft->setText(QString());
        radioBtnArmorRight->setText(QString());
        radioBtnArmorTop->setText(QString());
        radioBtnArmorBottom->setText(QString());
        radioBtnBrickFull->setText(QString());
        radioBtnBrickTop->setText(QString());
        radioBtnBrickLeft->setText(QString());
        radioBtnBrickRight->setText(QString());
        radioBtnBrickBottom->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MapEditorClass: public Ui_MapEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITOR_H
