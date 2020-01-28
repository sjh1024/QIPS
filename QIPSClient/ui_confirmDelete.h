/********************************************************************************
** Form generated from reading UI file 'confirmDelete.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMDELETE_H
#define UI_CONFIRMDELETE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_confirmDeleteBox
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *ipToDelete;

    void setupUi(QDialog *confirmDeleteBox)
    {
        if (confirmDeleteBox->objectName().isEmpty())
            confirmDeleteBox->setObjectName(QStringLiteral("confirmDeleteBox"));
        confirmDeleteBox->resize(616, 128);
        buttonBox = new QDialogButtonBox(confirmDeleteBox);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(250, 90, 181, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        ipToDelete = new QLabel(confirmDeleteBox);
        ipToDelete->setObjectName(QStringLiteral("ipToDelete"));
        ipToDelete->setGeometry(QRect(10, 10, 721, 71));

        retranslateUi(confirmDeleteBox);
        QObject::connect(buttonBox, SIGNAL(accepted()), confirmDeleteBox, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), confirmDeleteBox, SLOT(reject()));

        QMetaObject::connectSlotsByName(confirmDeleteBox);
    } // setupUi

    void retranslateUi(QDialog *confirmDeleteBox)
    {
        confirmDeleteBox->setWindowTitle(QApplication::translate("confirmDeleteBox", "Confirm Remove", Q_NULLPTR));
        ipToDelete->setText(QApplication::translate("confirmDeleteBox", "Are you sure you want to unblock this IP address?", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class confirmDeleteBox: public Ui_confirmDeleteBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMDELETE_H
