/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionApri;
    QAction *actionSalva;
    QAction *actionSalva_con_nome;
    QAction *actionCerca;
    QAction *actionNuovo;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextEdit *editor_testo;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(730, 575);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(100, 100));
        MainWindow->setMaximumSize(QSize(10000, 10000));
        actionApri = new QAction(MainWindow);
        actionApri->setObjectName(QString::fromUtf8("actionApri"));
        actionSalva = new QAction(MainWindow);
        actionSalva->setObjectName(QString::fromUtf8("actionSalva"));
        actionSalva_con_nome = new QAction(MainWindow);
        actionSalva_con_nome->setObjectName(QString::fromUtf8("actionSalva_con_nome"));
        actionCerca = new QAction(MainWindow);
        actionCerca->setObjectName(QString::fromUtf8("actionCerca"));
        actionNuovo = new QAction(MainWindow);
        actionNuovo->setObjectName(QString::fromUtf8("actionNuovo"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        editor_testo = new QTextEdit(centralwidget);
        editor_testo->setObjectName(QString::fromUtf8("editor_testo"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(editor_testo->sizePolicy().hasHeightForWidth());
        editor_testo->setSizePolicy(sizePolicy1);
        editor_testo->setMinimumSize(QSize(100, 100));
        editor_testo->setMaximumSize(QSize(999999, 999999));
        editor_testo->setLayoutDirection(Qt::LeftToRight);
        editor_testo->setLineWidth(0);

        gridLayout->addWidget(editor_testo, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 730, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionNuovo);
        menuFile->addAction(actionApri);
        menuFile->addSeparator();
        menuFile->addAction(actionSalva);
        menuFile->addAction(actionSalva_con_nome);
        menuEdit->addAction(actionCerca);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Editor Bello", nullptr));
        actionApri->setText(QCoreApplication::translate("MainWindow", "Apri", nullptr));
#if QT_CONFIG(shortcut)
        actionApri->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSalva->setText(QCoreApplication::translate("MainWindow", "Salva", nullptr));
#if QT_CONFIG(shortcut)
        actionSalva->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSalva_con_nome->setText(QCoreApplication::translate("MainWindow", "Salva con nome...", nullptr));
#if QT_CONFIG(shortcut)
        actionSalva_con_nome->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Alt+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCerca->setText(QCoreApplication::translate("MainWindow", "Cerca...", nullptr));
#if QT_CONFIG(shortcut)
        actionCerca->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNuovo->setText(QCoreApplication::translate("MainWindow", "Nuovo", nullptr));
#if QT_CONFIG(shortcut)
        actionNuovo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
