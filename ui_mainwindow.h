/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Thu Mar 12 21:28:39 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton;
    QLineEdit *leHost;
    QLineEdit *lePort;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
    if (MainWindowClass->objectName().isEmpty())
        MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
    MainWindowClass->resize(592, 400);
    centralWidget = new QWidget(MainWindowClass);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    tabWidget = new QTabWidget(centralWidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setGeometry(QRect(-10, 10, 591, 341));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    pushButton = new QPushButton(tab);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(20, 20, 83, 26));
    leHost = new QLineEdit(tab);
    leHost->setObjectName(QString::fromUtf8("leHost"));
    leHost->setGeometry(QRect(150, 20, 113, 26));
    lePort = new QLineEdit(tab);
    lePort->setObjectName(QString::fromUtf8("lePort"));
    lePort->setGeometry(QRect(270, 20, 51, 26));
    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    tabWidget->addTab(tab_2, QString());
    MainWindowClass->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(MainWindowClass);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 592, 24));
    MainWindowClass->setMenuBar(menuBar);
    mainToolBar = new QToolBar(MainWindowClass);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(MainWindowClass);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    MainWindowClass->setStatusBar(statusBar);

    retranslateUi(MainWindowClass);

    QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
    MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("MainWindowClass", "Conectar", 0, QApplication::UnicodeUTF8));
    leHost->setText(QApplication::translate("MainWindowClass", "localhost", 0, QApplication::UnicodeUTF8));
    lePort->setText(QApplication::translate("MainWindowClass", "80", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindowClass", "Conexion", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindowClass", "Tab 2", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(MainWindowClass);
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
