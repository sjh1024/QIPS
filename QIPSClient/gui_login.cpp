#include<gui_login.h>

qipsLoginUi::qipsLoginUi(QWidget * parent)
:QDialog( parent )
{
	setupUi( this );
	connect( this->loginButton, SIGNAL( clicked() ), this, SLOT( attemptToLogin() ) );
	
		
 
	
}
void qipsLoginUi::attemptToLogin() 
{
	
if( userBox->text().length() == 0 && passBox->text().length() == 0)
	{
		QMessageBox::critical( this, tr("Error"), tr("Please enter a username and password"));
		
	}	
	else if( userBox->text().length() == 0 )
	{
		QMessageBox::critical( this, tr("Error"), tr("Please enter a username"));
	
	}
	else if(passBox->text().length() == 0 )
	{
		QMessageBox::critical( this, tr("Error"), tr("Please enter a password"));
	
	}
	else
	{
		nClient = new netClient;
		connect( nClient, SIGNAL( error(QAbstractSocket::SocketError)), this, SLOT( reportErrors()));
		nClient->hostConnect();
		connect( nClient, SIGNAL( sentReply( std::string )), this, SLOT (processServerReply(std::string)) );
		QString uname = userBox->text();
		QString pw = passBox->text();
		//qWarning()<< "Attempted login: " << login->userBox->text() << " pass: " << login->passBox->text();
		QString loginquery = "login,"  + uname + "," + pw + "<*//*>";
		nClient->netClient::sendData(loginquery.toStdString());
		

	}
}
void qipsLoginUi::processServerReply( std::string reply )
{
	

	QString qReply = QString::fromStdString(reply );
	if( qReply.contains("SUCCESS"))
	{
		delete nClient;
		this->close();
		qips = new guiQIPS();
		qips->exec();

	}
	else if( qReply.contains("Incorrect login credentials, please try again."))
	{
		QMessageBox::critical( this, tr("Bad Login"), tr(qReply.toLocal8Bit()));
	}
	
	
}
void qipsLoginUi::reportErrors()
{	
	QString errormsg = "Could not connect to server: ";
	qWarning() << nClient->error();
	errormsg += nClient->errorString();
	QMessageBox::critical( this, tr("Login Error"), tr(errormsg.toLocal8Bit()));	

}
