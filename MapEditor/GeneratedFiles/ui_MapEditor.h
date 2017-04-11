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
        MapEditorClass->resize(537, 435);
        centralWidget = new QWidget(MapEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 501, 381));
        radioBtnBushes = new QRadioButton(groupBox);
        radioBtnBushes->setObjectName(QStringLiteral("radioBtnBushes"));
        radioBtnBushes->setGeometry(QRect(20, 10, 91, 81));
        radioBtnBushes->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/buttonIcons/BUSHES.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioBtnBushes->setIcon(icon);
        radioBtnBushes->setIconSize(QSize(64, 64));
        radioBtnWater = new QRadioButton(groupBox);
        radioBtnWater->setObjectName(QStringLiteral("radioBtnWater"));
        radioBtnWater->setGeometry(QRect(180, 30, 82, 17));
        radioBtnIce = new QRadioButton(groupBox);
        radioBtnIce->setObjectName(QStringLiteral("radioBtnIce"));
        radioBtnIce->setGeometry(QRect(350, 30, 82, 17));
        radioBtnArmorFull = new QRadioButton(groupBox);
        radioBtnArmorFull->setObjectName(QStringLiteral("radioBtnArmorFull"));
        radioBtnArmorFull->setGeometry(QRect(20, 120, 82, 17));
        radioBtnArmorLeft = new QRadioButton(groupBox);
        radioBtnArmorLeft->setObjectName(QStringLiteral("radioBtnArmorLeft"));
        radioBtnArmorLeft->setGeometry(QRect(20, 150, 82, 17));
        radioBtnArmorRight = new QRadioButton(groupBox);
        radioBtnArmorRight->setObjectName(QStringLiteral("radioBtnArmorRight"));
        radioBtnArmorRight->setGeometry(QRect(20, 180, 82, 17));
        radioBtnArmorTop = new QRadioButton(groupBox);
        radioBtnArmorTop->setObjectName(QStringLiteral("radioBtnArmorTop"));
        radioBtnArmorTop->setGeometry(QRect(20, 240, 82, 17));
        radioBtnArmorBottom = new QRadioButton(groupBox);
        radioBtnArmorBottom->setObjectName(QStringLiteral("radioBtnArmorBottom"));
        radioBtnArmorBottom->setGeometry(QRect(20, 210, 82, 17));
        radioBtnBrickFull = new QRadioButton(groupBox);
        radioBtnBrickFull->setObjectName(QStringLiteral("radioBtnBrickFull"));
        radioBtnBrickFull->setGeometry(QRect(180, 90, 82, 17));
        radioBtnBrickTop = new QRadioButton(groupBox);
        radioBtnBrickTop->setObjectName(QStringLiteral("radioBtnBrickTop"));
        radioBtnBrickTop->setGeometry(QRect(180, 210, 82, 17));
        radioBtnBrickLeft = new QRadioButton(groupBox);
        radioBtnBrickLeft->setObjectName(QStringLiteral("radioBtnBrickLeft"));
        radioBtnBrickLeft->setGeometry(QRect(180, 120, 82, 17));
        radioBtnBrickRight = new QRadioButton(groupBox);
        radioBtnBrickRight->setObjectName(QStringLiteral("radioBtnBrickRight"));
        radioBtnBrickRight->setGeometry(QRect(180, 150, 82, 17));
        radioBtnBrickBottom = new QRadioButton(groupBox);
        radioBtnBrickBottom->setObjectName(QStringLiteral("radioBtnBrickBottom"));
        radioBtnBrickBottom->setGeometry(QRect(180, 180, 82, 17));
        MapEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MapEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 537, 21));
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
        radioBtnWater->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnIce->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnArmorFull->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnArmorLeft->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnArmorRight->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnArmorTop->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnArmorBottom->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnBrickFull->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnBrickTop->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnBrickLeft->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnBrickRight->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
        radioBtnBrickBottom->setText(QApplication::translate("MapEditorClass", "RadioButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MapEditorClass: public Ui_MapEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITOR_H
