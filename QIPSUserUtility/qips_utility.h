#include <QObject>
#include <QSslSocket>
#include<iostream>
#include<QSslCertificate>
#include<QSslKey>


/*************************************************************************************************************
qips_utility.h
The header file for the qips_utility.cpp file.
sjh1024 1-8-2019
*******************************************************************************************************/


#ifndef ___UTILITY___
#define ___UTILITY___

class QIPSUtility : public QSslSocket
{

	Q_OBJECT
	public:
		QIPSUtility(QObject *parent = 0);
		void connectToServer();
		void setMode(int modeCode );
		void setUser(QString user );
	private:
		QSslKey key;
		QSslCertificate cert;
  int attempts;
  int mode;
		QString userToChange;
	public slots:
		virtual void establishConnection();
		virtual void readServerResponse();
		virtual void displayErrors( QList<QSslError> errors );
		//DEBUGGING METHODS BELOW//		
		virtual void isEncrypted();
		virtual void processChecks();
};
#endif
