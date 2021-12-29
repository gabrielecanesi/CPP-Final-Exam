/********************************************************************************
** Form generated from reading UI file 'finddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_FindDialog
{
public:
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox;
    QPushButton *button_find;
    QLabel *label_non_trovata;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *button_close;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *FindDialog)
    {
        if (FindDialog->objectName().isEmpty())
            FindDialog->setObjectName(QString::fromUtf8("FindDialog"));
        FindDialog->resize(350, 125);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FindDialog->sizePolicy().hasHeightForWidth());
        FindDialog->setSizePolicy(sizePolicy);
        FindDialog->setMinimumSize(QSize(350, 125));
        FindDialog->setMaximumSize(QSize(350, 125));
        gridLayout_2 = new QGridLayout(FindDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        checkBox = new QCheckBox(FindDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout_2->addWidget(checkBox, 1, 0, 1, 1);

        button_find = new QPushButton(FindDialog);
        button_find->setObjectName(QString::fromUtf8("button_find"));

        gridLayout_2->addWidget(button_find, 0, 2, 1, 1);

        label_non_trovata = new QLabel(FindDialog);
        label_non_trovata->setObjectName(QString::fromUtf8("label_non_trovata"));

        gridLayout_2->addWidget(label_non_trovata, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(FindDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(FindDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFrame(true);
        lineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit->setDragEnabled(true);
        lineEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(lineEdit);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        button_close = new QPushButton(FindDialog);
        button_close->setObjectName(QString::fromUtf8("button_close"));

        gridLayout_2->addWidget(button_close, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);


        retranslateUi(FindDialog);

        QMetaObject::connectSlotsByName(FindDialog);
    } // setupUi

    void retranslateUi(QDialog *FindDialog)
    {
        FindDialog->setWindowTitle(QCoreApplication::translate("FindDialog", "Cerca Testo", nullptr));
        checkBox->setText(QCoreApplication::translate("FindDialog", "Match case", nullptr));
        button_find->setText(QCoreApplication::translate("FindDialog", "Find", nullptr));
        label_non_trovata->setText(QString());
        label->setText(QCoreApplication::translate("FindDialog", "Find what:", nullptr));
        button_close->setText(QCoreApplication::translate("FindDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindDialog: public Ui_FindDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
