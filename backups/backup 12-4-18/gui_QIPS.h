#include <QObject>
#include <iostream>
#include <QWidget>
#include <QMessageBox>
#include<ui_QIPS.h>
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
#ifndef QIPSCLIENT
#define QIPSCLIENT
class guiQIPS : public QDialog, public Ui::QIPSbox
{ 
	Q_OBJECT 

public:
	guiQIPS(QWidget * parent = 0 );
	
	netClient *nClient = nullptr;
	//overridden eventFilter searches for right clicks on ListWidgetItems
	bool eventFilter(QObject *obj, QEvent *event); 
	void updateStats(QString oldipset);
	void createConfirmChange(int typeOfChange );
	QRegExpValidator * getIpValidator();
private:
QString deletequery = "";
QString addquery = "";
QString movequery = "";
QString renewquery = "";
QString blockquery = "";

QString currentIpset = "";
QString ipToBlock = "";
QString currentIp = "";
QString ipsetToMoveTo = "";

int unh = 0;
int spamhaus = 0;
int honeypot = 0;

public slots:
virtual void blockNewIp();
virtual void reportErrors(QAbstractSocket::SocketError error);
virtual void updateBlockedList();
virtual void renewEntry();
virtual void removeEntry();
virtual void moveEntry();
virtual void connectedToServer();
virtual void processServerReply(std::string reply);
virtual void searchForEntry();
virtual void removeConfirmed();
virtual void moveConfirmed();
virtual void renewConfirmed();
virtual void blockConfirmed();

signals:

};

#endif
