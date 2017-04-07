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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MapEditorClass)
    {
        if (MapEditorClass->objectName().isEmpty())
            MapEditorClass->setObjectName(QStringLiteral("MapEditorClass"));
        MapEditorClass->resize(600, 400);
        menuBar = new QMenuBar(MapEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MapEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MapEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MapEditorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MapEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MapEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MapEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MapEditorClass->setStatusBar(statusBar);

        retranslateUi(MapEditorClass);

        QMetaObject::connectSlotsByName(MapEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *MapEditorClass)
    {
        MapEditorClass->setWindowTitle(QApplication::translate("MapEditorClass", "MapEditor", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MapEditorClass: public Ui_MapEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITOR_H
