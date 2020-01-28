#include <QUuid>
#include <net_server.h>
#include <QTime>
#include <QString>
#include <iostream>
#include <QSqlError>
#include <string>
#include <map>
#include <random>

using namespace std;
netServer::netServer(int port, QObject *parent) :
  QTcpServer(parent)
{  

	username = QString::null;
	ips = QSqlDatabase::addDatabase("QSQLITE");
	
	QFile keyFile("nKey.key");
	if (keyFile.open(QIODevice::ReadOnly))
	{
	key = QSslKey(keyFile.readAll(), QSsl::Rsa);
	keyFile.close();
        }
	else
        {
	  fprintf(stderr,"Unable to open nKey.key\n");
          exit(-1);
        }


	QFile certFile("nKey.pem");
	if (certFile.open(QIODevice::ReadOnly))
        {
	cert = QSslCertificate(certFile.readAll());
	certFile.close();
        }
	else
        {
	  fprintf(stderr,"Unable to open nKey.key\n");
          exit(-1);
        }


	setMaxPendingConnections(1024);


 	if(!this->listen(QHostAddress::Any, port ))
 	{
		printf( "ERROR: SERVER COULD NOT START.\n" );
 	}
 	else
 	{
		printf( "QIPS SERVER HAS STARTED!\n" );	
 	} 
	QString path = QDir::currentPath();
	
}
void netServer::sslErrors(QList<QSslError> errors )
{
	QSslSocket* socket = (QSslSocket*)sender();
	QList<QSslError> errorsThatCanBeIgnored;
	errorsThatCanBeIgnored<<QSslError(QSslError::SelfSignedCertificateInChain,cert);
	errorsThatCanBeIgnored<<QSslError(QSslError::SelfSignedCertificate,cert);
	errorsThatCanBeIgnored<<QSslError(QSslError::CertificateUntrusted,cert);
	socket->ignoreSslErrors(errorsThatCanBeIgnored);
	for( int i = 0; i  < errors.size(); i++ )
	{
		qWarning() << errors.at(i);
	}
}
void netServer::incomingConnection(qintptr socketDescriptor)
{
	QSslSocket *sslSocket = new QSslSocket(this);
	connect(sslSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
	sslSocket->setSocketDescriptor(socketDescriptor);
	sslSocket->setPrivateKey(key);
	sslSocket->setLocalCertificate(cert);
	sslSocket->addCaCertificate(cert);
	sslSocket->setPeerVerifyMode(QSslSocket::VerifyPeer);
	sslSocket->startServerEncryption();
	fflush(stdout);
	this->pendingConnections.enqueue(sslSocket);
	connect(this, SIGNAL(newConnection()), this, SLOT( receiveConnection()));
}
void netServer::receiveConnection()
{
	fflush(stdout);
	while( pendingConnections.size() > 0 )
	{
		QSslSocket *socket = this->pendingConnections.dequeue();
	      	
		if (socket)
		{
	    
		  	socketData *sd = new socketData;	
		  	sd->socket = socket;
		  	sd->socket->setObjectName(QUuid::createUuid().toString());
		  	sd->data = QString::null;
			connect(sd->socket,SIGNAL(readyRead()),this,SLOT(receiveReadyRead()));
			connect(sd->socket,SIGNAL(disconnected()),this,SLOT(webDisconnected()));
		 	m_clients.append(sd); 
		}

	}

}
void netServer::receiveReadyRead()
{
	QSslSocket* socket = (QSslSocket*)sender(); 
  	char *rawdata = (char *)malloc(1025);
   	QByteArray response;
	fflush(stdout);



  	while(socket->bytesAvailable())
    	{
		QByteArray dt = socket->readAll();
		QString rd = QString::fromLocal8Bit(dt);
		//qWarning()<<rd;
		if((rd.contains("<//>", Qt::CaseInsensitive ) == false ) && (rd.contains ("<*//*>", Qt::CaseInsensitive) == false ))
		{
			//qWarning()<<"b";
      			response = "Invalid command. Please try again.\n";
      			socket->write( response );
		}
		else if( rd.contains("<//>", Qt::CaseInsensitive ) == true ) 
		{

			if(rd.contains("<//>", Qt::CaseInsensitive ))
			{	
				ips.setDatabaseName("/usr/local/honeypot/bin/db/qips.db");
				ips.open();	

				 data = (rd.section( "<//>", 0, 0 ) );

			if( data.startsWith( "getallblocked<&&>" ) )
			{
				
				if( data.contains("first", Qt::CaseInsensitive ) )
				{
					updateStats();
					socket->write( curStats.toLocal8Bit() );
					socket->flush();
					//qWarning()<< "first";
					QSqlQuery query("SELECT * FROM ipset WHERE  ((strftime('%s', 'now') - 14400 )  - strftime( '%s', timestamp )) < 86400" );
		   			while (query.next()) 
					{			
		       				QString d = "first" + query.value(1).toString() + "|" + query.value(2).toString() + "|" + query.value(3).toString() + "|"+ query.value(4).toString() + "|" + 			    			query.value(5).toString() + "|" + query.value(6).toString() + "|" + query.value(7).toString();
						QString metadata = query.value(0).toString();
						d += "<!!>";
						d += metadata;
						
						socket->write( d.toLocal8Bit(), d.length() + 1 );
						socket->flush();
							//qWarning()<< "first";

				 	}
				}
				else
				{
					
					
					//QString curTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
					//QString lastRefresh = data.section("<&&>", 1, 1);	
					//qWarning()<< lastRefresh;					
					//qWarning()<< curTime;
					QSqlQuery query("SELECT * FROM ipset WHERE  ((strftime('%s', 'now') - 14400 )  - strftime( '%s', timestamp )) < 86400"); 
					while (query.next()) 
					{			
			       				QString d = query.value(1).toString() + "|" + query.value(2).toString() + "|" + query.value(3).toString() + "|"+ query.value(4).toString() + "|" + 			    			query.value(5).toString() + "|" + query.value(6).toString() + "|" + query.value(7).toString();
							QString metadata = query.value(0).toString();
							d += "<!!>";
							d += metadata;
							//qWarning()<< d;
							socket->write( d.toLocal8Bit(), d.length() + 1 );
							socket->flush();
					 }
				}
				
				socket->write("scroll");
				socket->flush();
				socket->write("scroll");
				socket->flush();
			}
			//NOTE: ONLY using the block_ip script upon adding new addresses
			//Because deletions cannot cause unwanted blocks,
			//Moves should already be "approved" addresses,
			//and Renews should already be "approved" addresses.
			else if( data.startsWith( "DELETE" ) )
			{
		
				QString ipSet = data.section( "<%>", 1, 1 );
				//qWarning()<< "ipset:" << ipSet;
				QString ipAdd = data.section( "<%>", 2, 2 );
				//qWarning()<< "ipadd:" << ipAdd;
				QProcess *remove = new QProcess();
				remove->start("sudo", QStringList() << "ipset" << "-D" << ipSet << ipAdd );
				connect( remove, SIGNAL( started()), this, SLOT( processStarted() ));
				connect( remove, SIGNAL(error(QProcess::ProcessError)), this, SLOT( reportProcErrors(QProcess::ProcessError) ));
				connect( remove, SIGNAL( finished(int, QProcess::ExitStatus) ), this, SLOT( removalSuccessful() ));
				remove->waitForFinished();
				updateStats();
				socket->write( "done" );
				socket->flush();
			}
			else if( data.startsWith( "MOVE" ) )
			{	
				QString oldIpSet = data.section( "<%>", 1, 1 );
				QString newIpSet = data.section( "<%>", 2, 2 );
				QString ipAdd = data.section("<%>", 3,3 );
				QProcess *evictOld = new QProcess();
				QProcess *move = new QProcess();
				evictOld->start("sudo", QStringList() << "/usr/sbin/ipset" << "-D" << oldIpSet << ipAdd );
				evictOld->waitForFinished();
				move->start("sudo", QStringList() << "/usr/sbin/ipset" << "-A" << newIpSet << ipAdd );
				connect( move, SIGNAL( finished(int, QProcess::ExitStatus) ), this, SLOT( moveSuccessful() ));
				move->waitForFinished();				
				updateStats();
				socket->write( "done" );
				socket->flush();
			}
			else if( data.startsWith("Renew")) 
			{
				QString ipSet = data.section( "<%>", 1, 1 );
				QString ipAdd = data.section( "<%>", 2, 2 );
				QProcess *evictOld = new QProcess();
				QProcess *renew = new QProcess();
				evictOld->start("sudo", QStringList() << "/usr/sbin/ipset" << "-D" << ipSet << ipAdd );
				evictOld->waitForFinished();				
				renew->start("sudo", QStringList() << "/usr/sbin/ipset" << "-A" << ipSet << ipAdd );
				renew->waitForFinished();				
				connect( renew, SIGNAL( finished(int, QProcess::ExitStatus) ), this, SLOT( renewalSuccessful() ));
				connect( evictOld, SIGNAL(error(QProcess::ProcessError)), this, SLOT( reportProcErrors(QProcess::ProcessError) ));
				connect( renew, SIGNAL(error(QProcess::ProcessError)), this, SLOT( reportProcErrors(QProcess::ProcessError) ));
				updateStats();
				socket->write( "done" );
				socket->flush();
			}
			else if( data.startsWith( "block entry" ))
			{
				QString ipAdd = data.section( ",", 1, 1 );
				QString ipset = data.section( ",", 3 );
				//qWarning()<< ipset;
				QSqlQuery initQuery( "SELECT * FROM ipset WHERE ipset = '" + ipset + "' AND ipaddress = '"+ ipAdd + "' AND deleteFlag = 0" );
				if( initQuery.next() )
				{
					socket->write( "already exists" );
					socket->flush();
				}
				else
				{
					QProcess *add = new QProcess();
					add->setWorkingDirectory( "/usr/local/honeypot/bin" );
					add->start("/bin/sh", QStringList() << "block_ip" << ipset << ipAdd << "user" );
					connect( add, SIGNAL( finished(int, QProcess::ExitStatus) ), this, SLOT( addSuccessful(int ) ));					
					connect( add, SIGNAL(error(QProcess::ProcessError)), this, SLOT( reportProcErrors( QProcess::ProcessError) ));
					add->waitForFinished();
					int code = add->exitCode();

					if( code == 128 )
					{
						socket->write( add->readAllStandardError());
						socket->flush();
						updateStats();
						socket->write( "done" );
						socket->flush();
					}
					updateStats();
					socket->write( "done" );
					socket->flush();
				
				}
			}
			else if( data.startsWith( "updatestat" ))
			{
				updateStats();
				socket->write( curStats.toLocal8Bit() );
			}			
			else
		 	{
				//qWarning()<<"a";
				response = "Invalid command. Please try again.\n";
				socket->write( response );
				socket->flush();
			}
		
			std::string str = rd.toUtf8().constData();
			//std::cout<< "Received:"<< str << "\n";
			rd = (rd.section( "<//>", 1, -1 ) );
			socket->flush();
			
		    
	
		}
		

	}
	else //utility
	{	
		if(rd.contains("<*//*>", Qt::CaseInsensitive ))
		{
			
			ips.setDatabaseName("users.db");
			ips.open();
			
			data = (rd.section( "<*//*>", 0, 0 ) );
		
			
			if(data.contains("login"))
			{
				username = data.section( ",", 1, 1 );
				pass = data.section( ",", 2, 2 );
								
				QSqlQuery checkusername( "SELECT * FROM users WHERE username = '" + username + "'" );
				if( !checkusername.last() )
				{
					response = "Incorrect login credentials, please try again.";
					socket->write(response);
					socket->flush();
				}
				else
				{
					QCryptographicHash * hash = new QCryptographicHash(QCryptographicHash::Sha3_256);
					checkusername.last(); 
					QByteArray sal = checkusername.value(2).toByteArray();		
					QByteArray pw = checkusername.value(3).toByteArray();
					QByteArray salted = sal + pass.toLocal8Bit();
					QByteArray encrypted = hash->hash(salted, QCryptographicHash::Sha3_256);
					if( pw == encrypted )
					{
								
						response = "SUCCESS";
						socket->write(response);
						socket->flush();	
					}
					else
					{
						
						response = "Incorrect login credentials, please try again.";
						socket->write(response);
						socket->flush();
					}

				}
				
				
			}
			else if( data.contains("utility")  )
			{
				modeCode = (rd.section("<*//*>", 0, 0 ) );
				modeCode = (modeCode.section(",", 1, 1) );
				//qWarning()<< modeCode;
				if( QString::compare( modeCode, "0" ) == 0 )
				{
					response = "YOU ARE NOW CONNECTED TO THE QIPS NEW USER UTILITY. WELCOME.\nPlease enter your new username: ";
					socket->write( response );
					socket->flush();
				}
				else if( QString::compare( modeCode, "3" ) == 0 )
				{
					QSqlQuery query("SELECT username, admin FROM users" );
					QString listOfUsers = "username | admin\n";
		   			while (query.next()) 
					{			
						QString admin = "No";
						if( query.value(1) == 1 )
						{
							admin = "Yes";
						}
				
		       				QString d = "|" + query.value(0).toString() + "|" +  admin + "|\n";
						listOfUsers += d;
				 	}
					socket->write(listOfUsers.toLocal8Bit());
					socket->flush();
				}
				else 
				{
					response = "To  enter administrative mode, please enter admin username: ";
					socket->write( response );
					socket->flush();
				}
			} 
			else if( data.contains("usernameentry") )
			{
				username = data.section( ",", 0, 0 );
				if( username.length() < 2 )
				{	
					response = "Username must be at least 2 characters in length. \nPlease enter your new username:";
					socket->write( response );
					socket->flush();
				}
				else
				{
					QSqlQuery check( "SELECT COUNT(*) FROM users WHERE username = '" + username + "'" );
					if(check.next())
					{
						QString numOfUsers= check.value(0).toString();
						if( numOfUsers.toInt() > 0 )
						{
							response = "Username '" + username.toLocal8Bit() + "' already exists. \n Enter user's password to change password, or press Enter to quit: ";
							socket->write( response );
							socket->flush();
						}
						else
						{	
							response = "Welcome, " + username.toLocal8Bit() + "."  "\nPlease enter your desired password: ";
							socket->write( response );
							socket->flush();	
						}
					}
					

				}
			}
			else if( data.contains("adminuname") )
			{
				username = data.section( ",", 0, 0 );			
				QSqlQuery checkusername( "SELECT * FROM users WHERE username = '" + username + "'" );
						
				if( !checkusername.last() )
				{
					response = "Invalid username, please try again. \n To enter administrative mode, please enter admin username: ";
					socket->write(response);
					socket->flush();
				}
				else
				{
					checkusername.last();
					if( checkusername.value(4) == 0 )
					{
						response = "ERROR: USER IS NOT AN ADMINISTRATOR. THE UTILITY WILL NOW CLOSE.";
						socket->write(response);
						socket->flush();
					}
					else
					{
						response = "Welcome back, " + username.toLocal8Bit() + "."  "\nPlease enter admin's password: ";
						socket->write(response);
						socket->flush();
					}	
		
				}
			}
			else if( data.contains("adminpass") ) 
			{
				
				if( username == "" )
				{
					response = "ERROR: USERNAME NOT FOUND";
					socket->write(response);
					socket->flush();
				}
				else
				{
					pass = data.section( ",", 0, 0 );
					QSqlQuery checkusername( "SELECT * FROM users WHERE username = '" + username + "'" );
					checkusername.last(); 
					QCryptographicHash * hash = new QCryptographicHash(QCryptographicHash::Sha3_256);
					QByteArray sal = checkusername.value(2).toByteArray();		
					QByteArray pw = checkusername.value(3).toByteArray();
					QByteArray salted = sal + pass.toLocal8Bit();
					QByteArray encrypted = hash->hash(salted, QCryptographicHash::Sha3_256);
					if( pw == encrypted )
					{
						if( QString::compare( modeCode, "1" ) == 0 ) //delete
						{
							QString toDelete = data.section("#", 1, 1 );	
							if( QString::compare( toDelete, username ) == 0 )
							{
								socket->write("ERROR: You cannot delete yourself from the list of users!");
								socket->flush();
							}
							else
							{
								QSqlQuery findUser( "SELECT * FROM users WHERE username = '" + toDelete + "'" );
								if( !findUser.last() )
								{
									response = "ERROR: User" + toDelete.toLocal8Bit() + "does not exist.";
									socket->write(response);
									socket->flush();
								}
								else
								{
									QSqlQuery deleteUser( "DELETE FROM users WHERE username = '" + toDelete + "'" );
									response = toDelete.toLocal8Bit() + " has been removed from QIPS User database. They will no longer have access to the QIPS Client.";
									socket->write(response);
									socket->flush();
								}
							}
													
						}		
						else if( QString::compare( modeCode, "2" ) == 0 ) //add
						{
							QString toAdd = data.section("#", 1, 1 );
							if( QString::compare( toAdd, username ) == 0 )
							{
								socket->write("ERROR: You are already an administrator!");
								socket->flush();
							}
							else
							{
								QSqlQuery findUser( "SELECT * FROM users WHERE username = '" + toAdd + "'" );
								if( !findUser.last() )
								{
									response = "ERROR: User" + toAdd.toLocal8Bit() + "does not exist.";
									socket->write(response);
									socket->flush();
								}
								else
								{
									findUser.last();
									if( findUser.value(4) == 1 )
									{
										response = "ERROR: User" + toAdd.toLocal8Bit() + " is already an administrator!";
										socket->write(response);
										socket->flush();
									}
									QSqlQuery addUser( "UPDATE users SET admin = 1 WHERE username = '" + toAdd + "'" );
									response = toAdd.toLocal8Bit() + " has been given administrative privileges.";
									socket->write(response);
									socket->flush();
								}
							}						
						}
						
					} 
					else
					{
						
						response = "Password incorrect, please try again.";
						socket->write(response);
						socket->flush();
					}

				}
			}
			else if( data.contains("passentry") )
			{
				pass = data.section( ",", 0, 0 );
				if( pass.length() < 4 )
				{	
					response = "Password must be at least 4 characters in length. \nPlease enter your desired password:";
					socket->write( response );
					socket->flush();
				}
				else
				{
					response = "Confirm password: ";
					socket->write( response );
					socket->flush();	
				}			
			}
			else if( data.contains("confirmpass") )
			{
				if( QString::compare( pass, data.section( ",", 0, 0 ) ) == 0 )
					{
								
						std::random_device engine;
						long long unsigned int s = engine();
						std::string salt = std::to_string(s);
						QByteArray combo = salt.c_str() + pass.toLocal8Bit();
						QCryptographicHash * hash = new QCryptographicHash(QCryptographicHash::Sha3_256);
						//cout << salt;
						response = "Username '" + username.toLocal8Bit() + "' now has access to QIPSServer. You may now login with your credentials in the QIPSClient.\n"; 
						socket->write( response ); 
						socket->flush();
						//encrypt and store password username combo
					
						QByteArray encrypted = hash->hash(combo, QCryptographicHash::Sha3_256);
						QSqlQuery query = QSqlQuery(ips);
						query.prepare("INSERT INTO users (username, salt, pass, admin) VALUES( '" + username + "' , '" + QString::fromStdString(salt) + "', :pass, 0 )");
						query.bindValue(":pass", encrypted );
						if( !query.exec() )
        						qWarning() << "Error inserting user/pass combo into table:\n" << query.lastError();
						pass = "";
						username = "";
						ips.close();

					}
					else
					{
						response = "Passwords do not match. \nConfirm password: ";
						socket->write( response );
						socket->flush();	
					}
			}
			else if( data.contains("chpass") )
			{
				
				pass = data.section( ",", 0, 0 );			
				QSqlQuery checkusername( "SELECT * FROM users WHERE username = '" + username + "'" );
				if( !checkusername.last() )
				{
					response = "ERROR: USERNAME NOT FOUND.";
					socket->write(response);
					socket->flush();
				}
				else
				{
					QCryptographicHash * hash = new QCryptographicHash(QCryptographicHash::Sha3_256);
					checkusername.last(); 
					QByteArray sal = checkusername.value(2).toByteArray();		
					QByteArray pw = checkusername.value(3).toByteArray();
					QByteArray salted = sal + pass.toLocal8Bit();
					QByteArray encrypted = hash->hash(salted, QCryptographicHash::Sha3_256);
					if( pw == encrypted )
					{
								
						response = "Welcome back, " + username.toLocal8Bit() + "."  "\nPlease enter your new password: ";
						socket->write(response);
						socket->flush();	
					}
					else
					{
						
						response = "Incorrect password, please try again:";
						socket->write(response);
						socket->flush();
					}

				}
			}
			else if( data.contains( "enternew" ) )
			{
				pass = data.section( ",", 0, 0 );
				if( pass.length() < 4 )
				{	
					response = "Password must be at least 4 characters in length. \nPlease enter your new password:";
					socket->write( response );
					socket->flush();
				}
				else
				{
					response = "Confirm new password: ";
					socket->write( response );
					socket->flush();	
				}			
			}
			else if( rd. contains("confnew" ) )
			{
				if( QString::compare( pass, data.section( ",", 0, 0 ) ) == 0 )
				{
							
					std::random_device engine;
					long long unsigned int s = engine();
					std::string salt = std::to_string(s);
					QByteArray combo = salt.c_str() + pass.toLocal8Bit();
					QCryptographicHash * hash = new QCryptographicHash(QCryptographicHash::Sha3_256);
					//cout << salt;
					response = "Password change successful. You may now login with your new credentials in the QIPSClient.\n"; 
					socket->write( response ); 
					socket->flush();
					//encrypt and store password username combo
				
					QByteArray encrypted = hash->hash(combo, QCryptographicHash::Sha3_256);
					QSqlQuery query = QSqlQuery(ips);
					query.prepare("UPDATE users SET salt = '" + QString::fromStdString(salt) + "', pass = :pass WHERE username = '" + username.toLocal8Bit() + "'" );
					query.bindValue(":pass", encrypted );
					if( !query.exec() )
						qWarning() << "Error inserting user/pass combo into table:\n" << query.lastError();
					pass = "";
					username = "";
					ips.close();

				}
				else
				{
					response = "ERROR: Passwords do not match. \nConfirm new password: ";
					socket->write( response );
					socket->flush();	
				}
			}
			else
			{
				//INVALID COMMANDS; error message?
			}
			/*
			else
			{
				if( userpass == 1 ) //enter username
				{
					//qWarning() << "username entered";
					username = data.section( ",", 0, 0 );
					if( username.length() < 4 )
					{	
						response = "Username must be at least 4 characters in length. \nPlease enter your new username:";
						socket->write( response );
						socket->flush();
					}
					else
					{
						QSqlQuery check( "SELECT COUNT(*) FROM users WHERE username = '" + username + "'" );
						if(check.next())
						{
							QString numOfUsers= check.value(0).toString();
							if( numOfUsers.toInt() > 0 )
							{
								response = "Username '" + username.toLocal8Bit() + "' already exists. Please try again: ";
								socket->write( response );
								socket->flush();
							}
							else
							{	
								response = "Welcome, " + username.toLocal8Bit() + "."  "\nPlease enter your desired password: ";
								socket->write( response );
								socket->flush();	
							}
						}
						
					
					}
				}
				else if( userpass == 2 )
				{	
					pass = data.section( ",", 0, 0 );
					if( pass.length() < 4 )
					{	
						response = "Password must be at least 4 characters in length. \nPlease enter your desired password:";
						socket->write( response );
						socket->flush();
					}
					qWarning()<< pass;
					response = "Confirm password: ";
					socket->write( response );
					socket->flush();	
				}
				else if( userpass == 3 )
				{
					//qWarning() << data << " compared to " << pass;
					if( QString::compare( pass, data.section( ",", 0, 0 ) ) == 0 )
					{
								
						std::random_device engine;
						unsigned long int s = engine();
						std::string salt = std::to_string(s);
						QByteArray combo = salt.c_str() + pass.toLocal8Bit();
						QCryptographicHash * hash = new QCryptographicHash(QCryptographicHash::Sha3_256);
						//cout << salt;
						response = "Username '" + username.toLocal8Bit() + "' now has access to QIPSServer. You may now login with your credentials in the QIPSClient.\n"; 
						socket->write( response ); 
						socket->flush();
						//encrypt and store password username combo
					
						QByteArray encrypted = hash->hash(combo, QCryptographicHash::Sha3_256);
						qWarning() << encrypted;
						QSqlQuery query = QSqlQuery(ips);
						query.prepare("INSERT INTO users (username, salt, pass) VALUES( '" + username + "' , '" + QString::fromStdString(salt) + "', :pass )");
						query.bindValue(":pass", encrypted );
						if( !query.exec() )
        						qWarning() << "Error inserting user/pass combo into table:\n" << query.lastError();
						pass = "";
						username = "";
						ips.close();

					}
					else
					{
						response = "ERROR: Passwords do not match. \nConfirm password: ";
						socket->write( response );
						socket->flush();	
					}
				}
			
			} */
		}
	}
	


}


free(rawdata);
}
void netServer::updateStats()
{
	QString u;
	QString s;
	QString h;	
	QSqlQuery statQuery("select (select count(*) from ipset where ipset='unh' and ((strftime('%s', 'now') - 14400 )  - strftime( '%s', timestamp )) < 86400 and deleteFlag = 0),(select count(*) from ipset where ipset='spamhaus' and ((strftime('%s', 'now') - 14400 )  - strftime( '%s', timestamp )) < 86400 and deleteFlag = 0 ),(select count(*) from ipset where ipset='honeypot' and ((strftime('%s', 'now') - 14400 )  - strftime( '%s', timestamp )) < 86400 and deleteFlag = 0 )" );
	if(statQuery.next())
	{
		u = statQuery.value(0).toString();
		s = statQuery.value(1).toString();
		h = statQuery.value(2).toString();
	}	
	curStats = "<***>" + u + "." + s + "." + h ;
}
void netServer::reportProcErrors(QProcess::ProcessError error)
{
	qWarning() << "Error occurred:";
	qWarning() << error;
}
void netServer::removalSuccessful()
{
	//qWarning()<< "Removal successful.";
	QString primkey = data.section("<%>", 3, 3 );
	QString deletequery = "UPDATE ipset SET deleteFlag = 1 WHERE id = " + primkey;	
	QSqlQuery query( deletequery ); 
	
}
void netServer::renewalSuccessful()
{
	//qWarning()<< "Renewal successful.";  
	QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
	QString primkey = data.section("<%>", 3, 3 );
	QString renewquery = "UPDATE ipset SET timestamp = '" + date + "' WHERE id = " + primkey; 
	QSqlQuery query (renewquery);
	
}
void netServer::moveSuccessful()
{
	//qWarning()<< "Move successful.";
	QString primkey = data.section("<%>", 4, 4 );
	QString ipSet = data.section("<%>", 2, 2 );
	QString movequery = "UPDATE ipset SET ipset = '" + ipSet + "' WHERE id = " + primkey; 
	QSqlQuery query( movequery ); 

}
void netServer::addSuccessful( int i )
{
	//qWarning()<< "exit status:" << e;
	//qWarning()<< "exit code:" << i;
	//qWarning()<< "Add successful.";
	if( i == 128)
	{
		return;
	}
	else
	{
	QString ipAdd = data.section( ",", 1, 1 );
	QString ipset = data.section( ",", 3 );
	QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"); 
	}


}
void netServer::processStarted()
{
	//qWarning()<<"The process has started.";
}
void netServer::webDisconnected()
{
  QSslSocket* socket = (QSslSocket*)sender();
  int i;
  //qWarning()<<"Connection closed.";
  pass =  "";
  username = "";
  // Search for the socketData entry that has the QString we want to store our data in.
  for (i = 0; i < m_clients.size() && m_clients.at(i)->socket->objectName().compare(socket->objectName()) != 0; i++);

 
  fflush(stdout);
  m_clients.removeAt(i);
  
}

netServer::~netServer()
{

}

