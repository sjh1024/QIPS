/********************************************************************************
** Form generated from reading UI file 'confirmChange.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMCHANGE_H
#define UI_CONFIRMCHANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_confirmChangeBox
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *confirmQuestion;

    void setupUi(QDialog *confirmChangeBox)
    {
        if (confirmChangeBox->objectName().isEmpty())
            confirmChangeBox->setObjectName(QStringLiteral("confirmChangeBox"));
        confirmChangeBox->resize(616, 128);
        buttonBox = new QDialogButtonBox(confirmChangeBox);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(250, 90, 181, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        confirmQuestion = new QLabel(confirmChangeBox);
        confirmQuestion->setObjectName(QStringLiteral("confirmQuestion"));
        confirmQuestion->setGeometry(QRect(10, 10, 721, 71));

        retranslateUi(confirmChangeBox);
        QObject::connect(buttonBox, SIGNAL(accepted()), confirmChangeBox, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), confirmChangeBox, SLOT(reject()));

        QMetaObject::connectSlotsByName(confirmChangeBox);
    } // setupUi

    void retranslateUi(QDialog *confirmChangeBox)
    {
        confirmChangeBox->setWindowTitle(QApplication::translate("confirmChangeBox", "Confirm Action", Q_NULLPTR));
        confirmQuestion->setText(QApplication::translate("confirmChangeBox", "Are you sure you want to do this?", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class confirmChangeBox: public Ui_confirmChangeBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMCHANGE_H
