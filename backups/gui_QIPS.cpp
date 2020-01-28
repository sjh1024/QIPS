#include<gui_QIPS.h>
#include<gui_confirmChange.h>
#include<QTimer>
guiQIPS::guiQIPS(QWidget * parent)
:QDialog( parent )
{
	setupUi( this );
	this->blockedList->viewport()->installEventFilter(this);
	blockedList->blockSignals(false);
	connect(refreshButton, SIGNAL( clicked() ), this, SLOT( updateBlockedList() ) );
	connect(submitBlock, SIGNAL( clicked() ), this, SLOT(blockNewIp()));


	QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

	QRegExp ipRegex ("^" + ipRange
                 + "\\." + ipRange
                 + "\\." + ipRange
                 + "\\." + ipRange + "$");
	QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
	blockEntry->setValidator(ipValidator);
	
	//Refresh every 30 seconds
	QTimer *refresh = new QTimer(this);
	connect( refresh, SIGNAL(timeout()), this, SLOT(updateBlockedList()));
	refresh->start(30000);
 
}
bool guiQIPS::eventFilter(QObject *obj, QEvent *event)
{
	if( obj == blockedList->viewport() )
    	{
   		if( event->type() == QEvent::MouseButtonPress )
    		{
		
			QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);

    			if (MouseEvent->button() == Qt::RightButton ) 
			{
       			
				if(blockedList->itemAt(MouseEvent->pos()))
				{
					QPoint p = MouseEvent->pos();
					blockedList->setCurrentItem( blockedList->itemAt(MouseEvent->pos()));
				
					QMenu *entryOptions =  new QMenu(this);
					QAction *renew = new QAction( "Renew" );
					connect( renew, SIGNAL( triggered()), this, SLOT( renewEntry() ));
					//renew->setStatusTip( "Renew the entry's lockout time to its ipset's max...");
					QAction *remove = new QAction( "Remove" );
					connect( remove, SIGNAL( triggered()), this, SLOT( removeEntry() ));
					//remove->setStatusTip("Remove the entry from the blocked list...");
					QMenu *move = entryOptions->addMenu( "Move to ipset..." );
					
					QAction* moveToHoneypot = move->addAction("honeypot");
					QAction* moveToSpamhaus = move->addAction("spamhaus");
					QAction* moveToUserDefined = move->addAction("user-defined");
					QAction* moveToUNH = move->addAction("unh");

					connect( moveToHoneypot, SIGNAL( triggered()), this, SLOT( moveEntry() ) );
					connect( moveToSpamhaus, SIGNAL( triggered()), this, SLOT( moveEntry() ));
					connect( moveToUserDefined, SIGNAL( triggered()), this, SLOT( moveEntry()) );
					connect( moveToUNH, SIGNAL( triggered()), this, SLOT( moveEntry()) );	
					
					connect( move, SIGNAL( triggered()), this, SLOT( moveEntry() ));
					//move->setStatusTip("Move the entry to a different ipset...");
					QAction *metadata = new QAction( blockedList->itemAt(MouseEvent->pos())->data(Qt::UserRole).toString() );
					entryOptions->addAction(renew);
					entryOptions->addAction(remove);
					entryOptions->addAction(metadata);

					entryOptions->exec(MouseEvent->globalPos());
			
				}
       	 			return true;
			}
		}
  	} 
	else if( obj == blockIpset->viewport())
	{
		QMouseEvent *MEvent = static_cast<QMouseEvent *>(event);
		if( event->type() == QEvent::MouseButtonPress)
		{
			if(blockIpset->itemAt(MEvent->pos()))
			{
				blockIpset->setCurrentItem( blockIpset->itemAt(MEvent->pos()));
			}
			return true;
		}
	}
	
		return false;
}
void guiQIPS::blockNewIp()
{
	if( blockIpset->currentItem() == NULL )
	{
		QMessageBox::critical( this, tr("No ipset Selected"), tr("Please select an ipset to add to"));
	}
	else if( blockEntry->text().length() < 7 ||  blockEntry->text().section(".", 3,3 ) == "" )
	{
		QMessageBox::critical( this, tr("Invalid IP format"), tr("Please enter a valid IP address"));
	}
	else
	{
	QString ipToBlock = blockEntry->text();
	QString ipsetToAddTo = blockIpset->currentItem()->text();
	QString timestamp = QDateTime::currentDateTime().toString();
	//blockquery = "INSERT INTO ipset (ipaddress, reporter, process, ipset, description) VALUES( '" + ipToBlock + "' , 'User' , 'User' , '" + ipsetToAddTo + "' , '')<//>";
	blockquery = "block entry," + ipToBlock + ",in ipset," + ipsetToAddTo + "<//>";
	confirmChangeUi * confirm = new confirmChangeUi(); 
	QString stringToDisplay = "Are you sure you want to block ip address " + ipToBlock + "\n and place it into ipset " + ipsetToAddTo + "?";
	confirm->confirmQuestion->setText(stringToDisplay);
	connect( confirm, SIGNAL( accepted()), this, SLOT( blockConfirmed() ));
	confirm->exec();
	}
}
void guiQIPS::reportErrors(QAbstractSocket::SocketError error)
{	
	QString errormsg = "Could not refresh due to the following: ";
	errormsg += nClient->errorString();
	QMessageBox::critical( this, tr("Error Connecting To Server"), tr(errormsg.toLocal8Bit()));
	

}
void guiQIPS::updateBlockedList()
{

	nClient = new netClient;
	connect( nClient, SIGNAL( error(QAbstractSocket::SocketError)), this, SLOT( reportErrors( QAbstractSocket::SocketError )));
	nClient->hostConnect();
	connect( nClient, SIGNAL( connected()), this, SLOT(  connectedToServer()));	
	
}
void guiQIPS::connectedToServer()
{
	connect( nClient, SIGNAL( sentReply( std::string )), this, SLOT (processServerReply(std::string)) );
	blockedList->clear();
	nClient->sendData("getallblocked<//>");
	
}
void guiQIPS::processServerReply( std::string reply )
{
	
	
	QString qReply = QString::fromStdString(reply );
	if( qReply.contains("<***>"))
	{
		QString stats = qReply.section("<***>", -1);
		ipsetStats->setText(stats);
	}
	else if( qReply.contains("already exists"))
	{
		QMessageBox::critical( this, tr("Error"), tr("That address already exists in that ipset."));
	}
	else
	{
	QString qDate = qReply.section( "<!!>", -1 );	
	qReply = qReply.section( "<!!>", 0, 0 );
	///Create the ListWidgetItem
	QListWidgetItem *i = new QListWidgetItem( qReply, 0, QListWidgetItem::UserType);
	//Set some metadata; this line sets the date pulled from the line as a type of user role data of the item.
	i->setData( Qt::UserRole, qDate );
	blockedList->addItem(i);
	}
	
	
}
void guiQIPS::renewEntry()
{
	QString primkey = blockedList->currentItem()->data(Qt::UserRole).toString();
	renewquery = "Renew "+ primkey + "<//>";
	
	confirmChangeUi * confirm = new confirmChangeUi();
	connect( confirm, SIGNAL( accepted() ), this, SLOT( renewConfirmed() ));
	QString dataToDisplay = blockedList->currentItem()->text();
	QString stringToDisplay = "Are you sure you want to renew entry \n" + dataToDisplay + "?";	
	confirm->confirmQuestion->setText(stringToDisplay);
	confirm->setWindowTitle("Confirm Renewal");
	confirm->exec();
}
void guiQIPS::removeEntry(  )
{
	QString primkey = blockedList->currentItem()->data(Qt::UserRole).toString();
	deletequery = "DELETE FROM ipset WHERE id = " + primkey + ";<//>";
	confirmChangeUi *confirm = new confirmChangeUi();
	connect( confirm, SIGNAL( accepted()), this, SLOT( removeConfirmed() ));
	QString dataToDisplay = blockedList->currentItem()->text();
	QString stringToDisplay = "Are you sure you want to remove entry \n" + dataToDisplay + "\nfrom the blocklist?";	
	confirm->confirmQuestion->setText(stringToDisplay);
	confirm->setWindowTitle("Confirm Delete");
	confirm->exec();
	
}
void guiQIPS::blockConfirmed()
{
	nClient->sendData(blockquery.toStdString());
	this->updateBlockedList();
}
void guiQIPS::removeConfirmed()
{
	nClient->sendData(deletequery.toStdString());
	this->updateBlockedList();
}
void guiQIPS::moveConfirmed()
{
	nClient->sendData(movequery.toStdString());
	this->updateBlockedList();
}
void guiQIPS::renewConfirmed()
{
	nClient->sendData(renewquery.toStdString());
	this->updateBlockedList();

}
void guiQIPS::moveEntry( )
{
	QString ipsetToMoveTo = qobject_cast<QAction*>(sender())->text();

	QString primkey = blockedList->currentItem()->data(Qt::UserRole).toString();
	QString curIpset = blockedList->currentItem()->text().section('|', 4, 4 );
	if( QString::compare( ipsetToMoveTo, curIpset ) == 0 )
	{
		QString errormsg = "That entry is already in ipset ";
		errormsg += curIpset;
		QMessageBox::critical( this, tr("Already in ipset"), tr(errormsg.toLocal8Bit()));
	}
	else
	{
	movequery = "UPDATE ipset SET ipset = '" + ipsetToMoveTo + "' WHERE id = " + primkey + ";<//>";
	confirmChangeUi *confirm = new confirmChangeUi();
	connect( confirm, SIGNAL( accepted()), this, SLOT( moveConfirmed() ));
	QString dataToDisplay = blockedList->currentItem()->text();
	QString stringToDisplay = "Are you sure you want to move entry \n" + dataToDisplay + "\nfrom ipset  " + curIpset + " to ipset " + ipsetToMoveTo + "?";	
	confirm->confirmQuestion->setText(stringToDisplay);
	confirm->setWindowTitle("Confirm Move");
	confirm->exec();
	}
}

