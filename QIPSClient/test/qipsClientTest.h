#include <QObject>
#include <QObject>
#include <iostream>
#include <QWidget>
#include <QMessageBox>
#include<ui_QIPS.h>
#include<gui_QIPS.h>
#include<net_client.h>
#include <QString>
#include <QMenu>
#include<QAction>
#include<QPoint>
#include<QMouseEvent>
#include<QVariant>
#include<QListWidget>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>
#include<QTime>
#include<QTimer>
#include<QStringList>
#include<QScrollBar>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QProcess>

#ifndef __CLIENTTESTING___
#define __CLIENTTESTING___

class qipsClientTest: public QObject
{
	Q_OBJECT

public:
private:


private slots:

	/*void blockUserDefinedAddsIPToCorrectIpset();
	void blockUnhAddsIPToCorrectIpset();
	void blockHoneypotAddsIPToCorrectIpset();
	void blockSpamhausAddsIPToCorrectIpset();
	void moveEntryMovesSpamhausToHoneypot(); 
	void renewEntryRenewsEntryToCorrectRenewalTime(); */
	void refreshIntervalCorrectOnNoAction();
	void refreshIntervalCorrectOnNewSubmit();
	void addingWhitelistIPsResultsInFailure();
	void scrollValuesChangeCorrectlyOnRefreshWithNoNewVals();
	void scrollValuesChangeCorrectlyOnNewEntry();
	void addingDuplicateAddressResultsInFailure();
	void addingMultipleAddressesResultsInCorrectNumOfEntries();
	void statsUpdatedCorrectly();
};

#endif
