/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_loginBox
{
public:
    QLineEdit *userBox;
    QLineEdit *passBox;
    QLabel *userLabel;
    QLabel *passwordLabel;
    QPushButton *loginButton;

    void setupUi(QDialog *loginBox)
    {
        if (loginBox->objectName().isEmpty())
            loginBox->setObjectName(QStringLiteral("loginBox"));
        loginBox->resize(451, 140);
        userBox = new QLineEdit(loginBox);
        userBox->setObjectName(QStringLiteral("userBox"));
        userBox->setGeometry(QRect(90, 20, 351, 28));
        passBox = new QLineEdit(loginBox);
        passBox->setObjectName(QStringLiteral("passBox"));
        passBox->setGeometry(QRect(90, 60, 351, 28));
        passBox->setInputMask(QStringLiteral(""));
        passBox->setEchoMode(QLineEdit::Password);
        userLabel = new QLabel(loginBox);
        userLabel->setObjectName(QStringLiteral("userLabel"));
        userLabel->setGeometry(QRect(10, 20, 111, 31));
        passwordLabel = new QLabel(loginBox);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        passwordLabel->setGeometry(QRect(20, 60, 81, 20));
        loginButton = new QPushButton(loginBox);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(180, 100, 84, 28));

        retranslateUi(loginBox);

        QMetaObject::connectSlotsByName(loginBox);
    } // setupUi

    void retranslateUi(QDialog *loginBox)
    {
        loginBox->setWindowTitle(QApplication::translate("loginBox", "QIPSClient Login", Q_NULLPTR));
        passBox->setText(QString());
        userLabel->setText(QApplication::translate("loginBox", "User Name:", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("loginBox", "Password:", Q_NULLPTR));
        loginButton->setText(QApplication::translate("loginBox", "Log in", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class loginBox: public Ui_loginBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
