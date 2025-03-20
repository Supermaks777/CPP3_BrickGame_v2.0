/********************************************************************************
** Form generated from reading UI file 'qtviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTVIEWER_H
#define UI_QTVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTViewer
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QTViewer)
    {
        if (QTViewer->objectName().isEmpty())
            QTViewer->setObjectName("QTViewer");
        QTViewer->resize(800, 600);
        centralwidget = new QWidget(QTViewer);
        centralwidget->setObjectName("centralwidget");
        QTViewer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QTViewer);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        QTViewer->setMenuBar(menubar);
        statusbar = new QStatusBar(QTViewer);
        statusbar->setObjectName("statusbar");
        QTViewer->setStatusBar(statusbar);

        retranslateUi(QTViewer);

        QMetaObject::connectSlotsByName(QTViewer);
    } // setupUi

    void retranslateUi(QMainWindow *QTViewer)
    {
        QTViewer->setWindowTitle(QCoreApplication::translate("QTViewer", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTViewer: public Ui_QTViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTVIEWER_H
