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

#ifndef QIPSCLIENT
#define QIPSCLIENT
class guiQIPS : public QDialog, public Ui::QIPSbox
{ 
	Q_OBJECT 

public:
	guiQIPS(QWidget * parent = 0 );
	
	netClient *nClient = nullptr;
	//"check" methods check for valid input from the user.
	//bool checkIpset(QString ipsetInQuestion);
	//overridden eventFilter searches for right clicks on ListWidgetItems
	bool eventFilter(QObject *obj, QEvent *event); 

private:
QString deletequery = "";
QString addquery = "";
QString movequery = "";
QString renewquery = "";
QString blockquery = "";

public slots:
virtual void blockNewIp();
virtual void reportErrors(QAbstractSocket::SocketError error);
virtual void updateBlockedList();
virtual void renewEntry();
virtual void removeEntry();
virtual void moveEntry();
virtual void connectedToServer();
virtual void processServerReply(std::string reply);

virtual void removeConfirmed();
virtual void moveConfirmed();
virtual void renewConfirmed();
virtual void blockConfirmed();

signals:

};

#endif
