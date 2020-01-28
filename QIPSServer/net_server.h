#include <QList>
#include <QObject>
#include <QTcpServer>
#include <QSslSocket>
#include<iostream>
#include<QSslKey>
#include<QSslCertificate>
#include <QQueue>
#include<QProcess>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDir>
#include<QTest>
#include<QCryptographicHash>
/*
** Provides a network interface for a web application to
** connect.
*/

#ifndef __NETSERVER__
#define __NETSERVER__

class netServer : public QTcpServer
{

  typedef struct x_socketdata {
    QSslSocket * socket;
    QString      data;
  } socketData;
    

  Q_OBJECT
 public:
  /*! Constructor for the main server of this application. 
    \param port The port number to associate with.
    \param parent The QObject which will be this class's parent */
  netServer(int port, QObject *parent = 0); 
  /*! Destructor for this application */
  ~netServer();
void setSocket( qintptr descriptor );
void updateStats();

 private: 
  /*!  Stores web connections */
  QList<socketData*>     m_clients;
  QQueue<QSslSocket*>    pendingConnections;
  QString curStats;
  QSslKey key;
  QSslCertificate cert;
  QSslCertificate ca;
  QString data;
  QString modeCode;
  QString pass;
  QString username;
  int numOfItems;
  QSqlDatabase ips;

 public slots:
  /*! Respond to a new network connection. */
  virtual void receiveConnection();
/*! Called when the web client has data to read. */
  virtual void receiveReadyRead(); 
  /*! Called when the web client disconnects. */
  virtual void webDisconnected();
  virtual void incomingConnection(qintptr socketDescriptor);
  virtual void sslErrors(QList<QSslError> errors);
/*! Confirm that processes were successful. !*/
  virtual void removalSuccessful();
  virtual void renewalSuccessful();
  virtual void moveSuccessful();
  virtual void addSuccessful( int i );
 virtual void processStarted();
virtual void reportProcErrors(QProcess::ProcessError error);

 signals:
 

};

#endif
