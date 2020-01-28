#include <QList>
#include <QObject>
#include <QSslSocket>
#include<iostream>
#include<QSslCertificate>
#include<QSslKey>
#include<string>
/*
** Provides a network interface for a web application to
** connect.
*/

#ifndef __NETCLIENT__
#define __NETCLIENT__

class netClient : public QSslSocket
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
  netClient(QObject *parent = 0); 
  void hostConnect();
  void sendData(std::string cmd);
  /*! Destructor for this application */
  ~netClient();

 private: 
  /*!  Stores web connections */
  QList<socketData*>     m_clients;
  QSslSocket *socket;
  QSslKey key;
  QSslCertificate cert;


 public slots:
  /*! Establish a connection to the server. */
  virtual void establishConnection();
/*!Read in responses coming in from the server. */
  virtual void readResponse(); 

 //Displays any connection errors.
  virtual void displayError(QList<QSslError> error );
//Checks if the connection is encrypted//
  virtual void isEncrypted();
	

 signals:
//Emitted when a reply is sent back from the server, and has been parsed by the client.//
 void sentReply(std::string reply);


};

#endif
