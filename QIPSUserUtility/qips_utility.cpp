#include<qips_utility.h>
#include <QTime>
#include <QString>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <unistd.h>
/*************************************************************************************************************
qips_utility.cpp

This utility connects to the QIPS Server and allows users to generate a username/password
combination for use in the QIPS Client.

The utility requires usage of an issued SSL certificate to log in.
sjh1024 1-9-2019
*******************************************************************************************************/

using namespace std;

QIPSUtility::QIPSUtility(QObject * parent):
QSslSocket(parent)
{
		attempts = 0;
		mode = 0;
	connect( this, SIGNAL(connected()), this, SLOT(establishConnection()));
	connect( this, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(displayErrors(QList<QSslError>)));
	connect( this, SIGNAL(encrypted()), this, SLOT(isEncrypted()));
	
	QFile keyFile("../QIPSServer/nKey.key");
	keyFile.open(QIODevice::ReadOnly);
	key = QSslKey(keyFile.readAll(), QSsl::Rsa);
	keyFile.close();

	QFile certFile("../QIPSServer/nKey.pem");
	certFile.open(QIODevice::ReadOnly);
	cert = QSslCertificate(certFile.readAll());
	certFile.close();

	this->setLocalCertificate(cert);
	this->setPrivateKey(key);
}
void QIPSUtility::connectToServer()
{	
	this->connectToHostEncrypted( "localhost", 4998 );
}
void QIPSUtility::establishConnection()
{
	connect(this, SIGNAL(readyRead()), this, SLOT(readServerResponse()));
	this->write("utility," + QString::number(mode).toLocal8Bit() + "<*//*>" );
	this->flush();
}
void QIPSUtility::readServerResponse()
{
	QSslSocket* serv = (QSslSocket*)sender();

	QByteArray dt = serv->readAll();
	QString rd = QString::fromLocal8Bit(dt);
	std::string str = rd.toUtf8().constData();
	//std::cout<< ""<< str;
	//std::cout.flush();
	if( rd.contains( "now has access to QIPSServer. You may now login with your credentials in the QIPSClient.\n" ) || rd.contains("Password change successful. You may now login with your new credentials in the QIPSClient."))
	{
		exit(0);	
	}
	else if( rd.contains( "Please enter your new username:" ) )
	{
		string s;
		cin >> s;
		s += ",usernameentry<*//*>";
		//cout<<"String inputted:"<<s<<endl;;
		serv->write(s.c_str());
		serv->flush();
	}
	else if( rd.contains( "To enter administrative mode, please enter admin username:"))
	{	
		string s;
		cin >> s;
		s += ",adminuname<*//*>";
		//cout<<"String inputted:"<<s<<endl;;
		serv->write(s.c_str());
		serv->flush();
	}
	else if( rd.contains( "Enter user's password to change password, or press Enter to quit:"))
	{
		char * p = getpass( "" );
		char * terminator = ",chpass<*//*>" ;
		std::string pass(p);
		if( pass.length() == 0 )
		{
			exit(-1);
		}
		pass.append(terminator);
		serv->write(pass.c_str());
		serv->flush();
	}
	else if( rd.contains( "Please enter admin's password:"))
	{
		char * p = getpass( "" );
	
		char * terminator = ",adminpass#" ;
		std::string pass(p);
		if( pass.length() == 0 )
		{
			exit(-1);
		}
		pass.append(terminator);
		pass.append( userToChange.toStdString() + "<*//*>" );
		serv->write(pass.c_str());
		serv->flush();
	}
	else if( rd.contains( "Please enter your desired password:") ) 
	{
		char * p = getpass( "" );
		char * terminator = ",passentry<*//*>" ;
		std::string pass(p);
		if( pass.length() == 0 )
		{
			exit(-1);
		}
		pass.append(terminator);
		serv->write(pass.c_str());
		serv->flush();
	}
	else if( rd.contains( "Confirm password:"))
	{
		if( attempts > 3 )
		{
			cout << "\nFAILED TO ADD NEW USER! Please try again.\n";
			exit(0);
		}
		else
		{	
			char * p = getpass( "" );	
			char * terminator = ",confirmpass<*//*>" ;
			std::string pass(p);
			if( pass.length() == 0 )
			{
				exit(-1);
			}
			else
			{
			pass.append(terminator);
			attempts++;
			serv->write(pass.c_str());
			serv->flush();
			}	
		}
	}
	else if( rd.contains( "ERROR" ))
	{
		cout<<endl;
		exit(-1);
	}
	else if( rd.contains( "Incorrect password, please try again:" )) //change pass
	{
		if( attempts >= 3 )
		{
			cout << "\nCould not authenticate, please try again.\n";
			exit(0);
		}
		else
		{
			char * p = getpass( "" );
			char * terminator = ",chpass<*//*>" ;
			std::string pass(p);
			if( pass.length() == 0 )
			{
				exit(-1);
			}
			pass.append(terminator);
			serv->write(pass.c_str());
			serv->flush();
			attempts++;
		}
	}
	else if( rd.contains( "Password incorrect, please try again" )) //admin pass
	{
		if( attempts >= 3 )
		{
			cout << "\nCould not authenticate, please try again.\n";
			exit(0);
		}
		else
		{
			char * p = getpass( "" );
			char * terminator = ",adminpass#" ;
			std::string pass(p);
			if( pass.length() == 0 )
			{
				exit(-1);
			}
			pass.append(terminator);
			pass.append( userToChange.toStdString() + "<*//*>" );
			serv->write(pass.c_str());
			serv->flush();
			attempts++;
		}
	}
	else if( rd.contains( "Please enter your new password:" ) )
	{
		char * p = getpass( "" );
		char * terminator = ",enternew<*//*>" ;
		std::string pass(p);
		if( pass.length() == 0 )
		{
			exit(-1);
		}
		pass.append(terminator);
		serv->write(pass.c_str());
		serv->flush();
	}
	else if( rd.contains( "Confirm new password:" ) )
	{
		char * p = getpass( "" );
		char * terminator = ",confnew<*//*>" ;
		std::string pass(p);
		if( pass.length() == 0 )
		{
			exit(-1);
		}
		pass.append(terminator);
		serv->write(pass.c_str());
		serv->flush();
	}
	else if( rd.contains("has been removed from QIPS User database. They will no longer have access to the QIPS Client." ) )
	{
		cout << endl;
		exit(0);
	}
	else if( rd.contains(" has been given administrative privileges."))
	{
		cout << endl;
		exit(0);
	}
	else if( rd.contains("username | admin"))
	{
		cout << endl;
		exit(0);
	}
	else
	{
		cout << "\nAn unknown error has occurred communicating with the server. The utility will now close.\n";
		exit(-1);
	}
		

}
void QIPSUtility::setMode(int modeCode )
{
	mode = modeCode;
}
void QIPSUtility::setUser(QString user )
{
	userToChange = user;
}
void QIPSUtility::displayErrors(QList<QSslError> errors)
{
	//qWarning()<< "An error occurred.";
	this->ignoreSslErrors();
	for( int i = 0; i  < errors.size(); i++ )
	{
		qWarning() << errors.at(i);
	}
}
void QIPSUtility::isEncrypted()
{
}
void QIPSUtility::processChecks()
{
	qWarning()<<"The process is started";
}
