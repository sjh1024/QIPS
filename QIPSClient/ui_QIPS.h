/********************************************************************************
** Form generated from reading UI file 'QIPS.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QIPS_H
#define UI_QIPS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QIPSbox
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *curBlockLabel;
    QTreeWidget *blockTree;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *refreshButton;
    QSpacerItem *horizontalSpacer_4;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *ipsetStatLabel;
    QTextEdit *ipsetStats;
    QLabel *blockLabel;
    QLineEdit *blockEntry;
    QLabel *label;
    QListWidget *blockIpset;
    QPushButton *searchButton;
    QLineEdit *searchLineEdit;
    QLabel *searchLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *submitBlock;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *QIPSbox)
    {
        if (QIPSbox->objectName().isEmpty())
            QIPSbox->setObjectName(QStringLiteral("QIPSbox"));
        QIPSbox->resize(1300, 624);
        gridLayout_3 = new QGridLayout(QIPSbox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        curBlockLabel = new QLabel(QIPSbox);
        curBlockLabel->setObjectName(QStringLiteral("curBlockLabel"));
        curBlockLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(curBlockLabel);

        blockTree = new QTreeWidget(QIPSbox);
        blockTree->setObjectName(QStringLiteral("blockTree"));
        blockTree->setMinimumSize(QSize(0, 500));
        blockTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        blockTree->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        blockTree->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        blockTree->setAutoScroll(false);
        blockTree->setAlternatingRowColors(false);

        verticalLayout_3->addWidget(blockTree);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        refreshButton = new QPushButton(QIPSbox);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));

        horizontalLayout_2->addWidget(refreshButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_2);


        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 1, 1);

        frame = new QFrame(QIPSbox);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(200, 0));
        frame->setMaximumSize(QSize(300, 16777215));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        ipsetStatLabel = new QLabel(frame);
        ipsetStatLabel->setObjectName(QStringLiteral("ipsetStatLabel"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ipsetStatLabel->sizePolicy().hasHeightForWidth());
        ipsetStatLabel->setSizePolicy(sizePolicy);
        ipsetStatLabel->setMinimumSize(QSize(200, 0));
        ipsetStatLabel->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(ipsetStatLabel, 0, 0, 1, 1);

        ipsetStats = new QTextEdit(frame);
        ipsetStats->setObjectName(QStringLiteral("ipsetStats"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ipsetStats->sizePolicy().hasHeightForWidth());
        ipsetStats->setSizePolicy(sizePolicy1);
        ipsetStats->setMinimumSize(QSize(200, 0));
        ipsetStats->setMaximumSize(QSize(300, 16777215));
        ipsetStats->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(ipsetStats, 1, 0, 1, 1);

        blockLabel = new QLabel(frame);
        blockLabel->setObjectName(QStringLiteral("blockLabel"));
        sizePolicy.setHeightForWidth(blockLabel->sizePolicy().hasHeightForWidth());
        blockLabel->setSizePolicy(sizePolicy);
        blockLabel->setMinimumSize(QSize(200, 0));
        blockLabel->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(blockLabel, 5, 0, 1, 1);

        blockEntry = new QLineEdit(frame);
        blockEntry->setObjectName(QStringLiteral("blockEntry"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(blockEntry->sizePolicy().hasHeightForWidth());
        blockEntry->setSizePolicy(sizePolicy2);
        blockEntry->setMinimumSize(QSize(200, 0));
        blockEntry->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(blockEntry, 6, 0, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(200, 0));
        label->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(label, 7, 0, 1, 1);

        blockIpset = new QListWidget(frame);
        new QListWidgetItem(blockIpset);
        new QListWidgetItem(blockIpset);
        new QListWidgetItem(blockIpset);
        new QListWidgetItem(blockIpset);
        blockIpset->setObjectName(QStringLiteral("blockIpset"));
        sizePolicy1.setHeightForWidth(blockIpset->sizePolicy().hasHeightForWidth());
        blockIpset->setSizePolicy(sizePolicy1);
        blockIpset->setMinimumSize(QSize(200, 0));
        blockIpset->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(blockIpset, 8, 0, 1, 1);

        searchButton = new QPushButton(frame);
        searchButton->setObjectName(QStringLiteral("searchButton"));

        gridLayout->addWidget(searchButton, 4, 0, 1, 1);

        searchLineEdit = new QLineEdit(frame);
        searchLineEdit->setObjectName(QStringLiteral("searchLineEdit"));

        gridLayout->addWidget(searchLineEdit, 3, 0, 1, 1);

        searchLabel = new QLabel(frame);
        searchLabel->setObjectName(QStringLiteral("searchLabel"));

        gridLayout->addWidget(searchLabel, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        submitBlock = new QPushButton(frame);
        submitBlock->setObjectName(QStringLiteral("submitBlock"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(submitBlock->sizePolicy().hasHeightForWidth());
        submitBlock->setSizePolicy(sizePolicy3);
        submitBlock->setMinimumSize(QSize(80, 28));

        horizontalLayout->addWidget(submitBlock);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_3->addWidget(frame, 0, 1, 1, 1);


        retranslateUi(QIPSbox);

        QMetaObject::connectSlotsByName(QIPSbox);
    } // setupUi

    void retranslateUi(QDialog *QIPSbox)
    {
        QIPSbox->setWindowTitle(QApplication::translate("QIPSbox", "QIPS", Q_NULLPTR));
        curBlockLabel->setText(QApplication::translate("QIPSbox", "List of Currently Blocked Addresses", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = blockTree->headerItem();
        ___qtreewidgetitem->setText(5, QApplication::translate("QIPSbox", "Description", Q_NULLPTR));
        ___qtreewidgetitem->setText(4, QApplication::translate("QIPSbox", "ipset", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("QIPSbox", "Process", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("QIPSbox", "Reporter", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("QIPSbox", "IP Address", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("QIPSbox", "Time of Block", Q_NULLPTR));
        refreshButton->setText(QApplication::translate("QIPSbox", "Refresh All", Q_NULLPTR));
        ipsetStatLabel->setText(QApplication::translate("QIPSbox", "Current ipset Statistics:", Q_NULLPTR));
        blockLabel->setText(QApplication::translate("QIPSbox", "Add an IP to the Blocklist:", Q_NULLPTR));
        blockEntry->setText(QString());
        blockEntry->setPlaceholderText(QApplication::translate("QIPSbox", "Enter an IP Address...", Q_NULLPTR));
        label->setText(QApplication::translate("QIPSbox", "Select ipset to Add Blocked IP to:", Q_NULLPTR));

        const bool __sortingEnabled = blockIpset->isSortingEnabled();
        blockIpset->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = blockIpset->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("QIPSbox", "user-defined", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem1 = blockIpset->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("QIPSbox", "unh", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem2 = blockIpset->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("QIPSbox", "honeypot", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem3 = blockIpset->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("QIPSbox", "spamhaus", Q_NULLPTR));
        blockIpset->setSortingEnabled(__sortingEnabled);

        searchButton->setText(QApplication::translate("QIPSbox", "Search", Q_NULLPTR));
        searchLabel->setText(QApplication::translate("QIPSbox", "Search for an IP Address...", Q_NULLPTR));
        submitBlock->setText(QApplication::translate("QIPSbox", "Block", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QIPSbox: public Ui_QIPSbox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QIPS_H
