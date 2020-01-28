#include <QWidget>
#include <QMessageBox>
#include<ui_login.h>
#include <ui_QIPS.h>
#include<net_client.h>
#include <gui_QIPS.h>
#ifndef __QIPSLOGIN__
#define __QIPSLOGIN__
class qipsLoginUi : public QDialog, public Ui::loginBox
{ 
	Q_OBJECT 

public:
	qipsLoginUi(QWidget * parent = 0 );
	
	
private:
	netClient * nClient; 
	guiQIPS * qips;
	
public slots:
	virtual void attemptToLogin();
	virtual void processServerReply(std::string);
	virtual void reportErrors();
signals:

};

#endif
