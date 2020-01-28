#include <QFile>
#include <QUuid>
#include <net_client.h>
#include <QTime>
#include <QString>
#include<iostream>
#include<QDebug>

using namespace std;
netClient::netClient(QObject *parent):
QSslSocket(parent)

{
	
	//Signal and slot intialization for establishing connection, displaying connection errors, and confirming if connection is encrypted.
	connect(this, SIGNAL(connected()), this, SLOT(establishConnection()));
	connect(this, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(displayError(QList<QSslError>)));
	connect( this, SIGNAL(encrypted()), this, SLOT(isEncrypted()));

	//Prepare client for encrypted communication with qips-server.
	QFile keyFile("nKey.key");
	keyFile.open(QIODevice::ReadOnly);
	key = QSslKey(keyFile.readAll(), QSsl::Rsa);
	keyFile.close();

	QFile certFile("nKey.pem");
	certFile.open(QIODevice::ReadOnly);
	cert = QSslCertificate(certFile.readAll());
	certFile.close();

	this->setLocalCertificate(cert);
 	this->addCaCertificate(cert);
	this->setPrivateKey(key);
	

	




}
//Connects the client to the server.
void netClient::hostConnect()
{
	this->ignoreSslErrors();
	this->connectToHostEncrypted( "localhost", 4998 );

}
void netClient::hostDisconnect()
{
this->ignoreSslErrors();
this->disconnectFromHost();

}
//Displays a list of errors, if they occur.
void netClient::displayError(QList<QSslError> errors )
{
	QList<QSslError> errorsThatCanBeIgnored;
	errorsThatCanBeIgnored<<QSslError(QSslError::SelfSignedCertificateInChain);
	errorsThatCanBeIgnored<<QSslError(QSslError::SelfSignedCertificate);
	errorsThatCanBeIgnored<<QSslError(QSslError::CertificateUntrusted);
	this->ignoreSslErrors();

	qWarning()<< "An error occurred.";

	//qWarning()<< errors.at(0);

}
//Confirms that the connection to the server is established, then allows client to read responses from the server upon readyRead.
void netClient::establishConnection()
{
	connect(this, SIGNAL(readyRead()), this, SLOT(readResponse()));
}
//Reads responses from the server.
void netClient::readResponse()
{
	
	QSslSocket* serv = (QSslSocket*)sender();

	
	if(serv->bytesAvailable())
	{

		QByteArray dt = serv->readAll();
		QString rd = QString::fromLocal8Bit(dt);
		std::string str = rd.toUtf8().constData();
		//std::cout<< ""<< str;
	//qipsClientUI needs to know this information
		emit sentReply(str);

	}
	

	


	

}
//Sends a specific string of data to the server as a command.
//Created for the qipsClientUI.
void netClient::sendData(std::string cmd)
{
	//Send "cmd" as a command
	//hostConnect();
	this->write(cmd.c_str());
	this->flush();	


	//Read the response and display it
	QByteArray dt = this->readAll();
	QString rd = QString::fromLocal8Bit(dt);
	std::string str = rd.toUtf8().constData();
	//std::cout<< ""<< cmd;

}
//Confirms that the connection is encrypted.
//Used for debugging purposes; currently not in use.
void netClient::isEncrypted()
{
	//printf( "Your connection is encrypted.\n");
	//fflush(stdout);
}

netClient::~netClient()
{

}

