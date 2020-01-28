#include<gui_QIPS.h>
using namespace std;
guiQIPS::guiQIPS(QWidget * parent)
:QDialog( parent )
{
	setupUi(this);
	
	deletequery = "";
	addquery = "";
	movequery = "";
	renewquery = "";
	blockquery = "";
	
	currentIpset = "";
	ipToBlock = "";
	currentIp = "";
	ipsetToMoveTo = "";
	curPrimKey = "";
	
	unh = 0;
	spamhaus = 0;
	honeypot = 0;
	refreshInterval = 30000;
	first = 0;
	newEntries = 0;
	numOfItems = 0;
	totEntries = 0;
	recentTime = QDateTime::fromString("1970-01-01 00:00:00", "yyyy-MM-dd HH:mm:ss");
	
	nClient = new netClient;

	this->blockTree->viewport()->installEventFilter(this);


	blockTree->blockSignals(false);
	//Connect button clicks to respective slots 
	connect(refreshButton, SIGNAL( clicked() ), this, SLOT( updateBlockedList() ) );
	connect(submitBlock, SIGNAL( clicked() ), this, SLOT(blockNewIp()));
	connect(searchButton, SIGNAL( clicked() ), this, SLOT( searchForEntry()));


	//Change the column widths so you can see everything
	blockTree->setColumnWidth(0, 200);
	blockTree->setColumnWidth(1, 150);
	blockTree->setColumnWidth(3, 250);
	
	//setValidators.
	QRegExpValidator *ipValidator = guiQIPS::getIpValidator();
	blockEntry->setValidator(ipValidator);
	searchLineEdit->setValidator(ipValidator);
	

	//Refresh every 30 seconds, beginning on login
	refresh = new QTimer(this);
	connect( refresh, SIGNAL(timeout()), this, SLOT(updateBlockedList()));
	refresh->start(refreshInterval);
	updateBlockedList();
}
void guiQIPS::closeClient()
{
	exit(0);
}
bool guiQIPS::eventFilter(QObject *obj, QEvent *event)
{
	if( event->type() == QEvent::MouseButtonPress || event->type() == QEvent::KeyPress )
	{
		refresh->start(refreshInterval);
	}
	if( obj == blockTree->viewport() )
    	{
   		if( event->type() == QEvent::MouseButtonPress )
    		{
		
			QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);

    			if (MouseEvent->button() == Qt::RightButton ) 
			{
       			
				if(blockTree->itemAt(MouseEvent->pos()))
				{
					
					blockTree->setCurrentItem( blockTree->itemAt(MouseEvent->pos()));
					//create right click menu
					QMenu *entryOptions =  new QMenu(this);
					QAction *renew = new QAction( "Renew",this );
					connect( renew, SIGNAL( triggered()), this, SLOT( renewEntry() ));
					QAction *remove = new QAction( "Remove",this );
					connect( remove, SIGNAL( triggered()), this, SLOT( removeEntry() ));
					QMenu *move = entryOptions->addMenu( "Move to ipset..." );
					//submenu for move to ipset					
					QAction* moveToHoneypot = move->addAction("honeypot");
					QAction* moveToSpamhaus = move->addAction("spamhaus");
					QAction* moveToUserDefined = move->addAction("user-defined");
					QAction* moveToUNH = move->addAction("unh");
					//connect signals/slots for menu item selection
					connect( moveToHoneypot, SIGNAL( triggered()), this, SLOT( moveEntry() ) );
					connect( moveToSpamhaus, SIGNAL( triggered()), this, SLOT( moveEntry() ));
					connect( moveToUserDefined, SIGNAL( triggered()), this, SLOT( moveEntry()) );
					connect( moveToUNH, SIGNAL( triggered()), this, SLOT( moveEntry()) );	
					connect( move, SIGNAL( triggered()), this, SLOT( moveEntry() ));
					
					entryOptions->addAction(renew);
					entryOptions->addAction(remove);
				
					//make the menu appear!
					entryOptions->exec(MouseEvent->globalPos());
			
				}
       	 			return true;
			}
		}
  	} 
	//Sets the clicked item on the blocklist as current item for other functions.
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
		ipToBlock = blockEntry->text();
		ipsetToMoveTo = blockIpset->currentItem()->text();
		blockquery = "block entry," + ipToBlock + ",in ipset," + ipsetToMoveTo + "<//>";
		guiQIPS::createConfirmChange(1);
	} 
}
void guiQIPS::blockConfirmed()
{
	nClient->netClient::sendData(blockquery.toStdString());
	
}
void guiQIPS::renewEntry()
{
	curPrimKey = blockTree->currentItem()->data(0, Qt::UserRole).toString();
	currentIp = blockTree->currentItem()->text(1);
	currentIpset = blockTree->currentItem()->text(4);
	renewquery = "Renew<%>" + currentIpset + "<%>" + currentIp + "<%>" + curPrimKey + "<//>";
	guiQIPS::createConfirmChange(3);
}
void guiQIPS::renewConfirmed()
{
	nClient->netClient::sendData(renewquery.toStdString());
	//updateBlockedList();
	
}
void guiQIPS::removeEntry(  )
{
	curPrimKey = blockTree->currentItem()->data(0, Qt::UserRole).toString();
	currentIp = blockTree->currentItem()->text(1);
	currentIpset = blockTree->currentItem()->text(4);
	deletequery = "DELETE<%>" + currentIpset + "<%>" + currentIp + "<%>" + curPrimKey + "<//>";
	guiQIPS::createConfirmChange(0);
	
}
void guiQIPS::removeConfirmed()
{
	nClient->netClient::sendData(deletequery.toStdString());
	//updateBlockedList();

	//delete blockTree->currentItem();
}
void guiQIPS::moveEntry( )
{
	ipsetToMoveTo = qobject_cast<QAction*>(sender())->text();
	curPrimKey = blockTree->currentItem()->data(0, Qt::UserRole).toString();
	currentIp = blockTree->currentItem()->text(1);
	currentIpset = blockTree->currentItem()->text(4);
	if( QString::compare( ipsetToMoveTo, currentIpset ) == 0 )
	{
	
		QMessageBox::critical( this, tr("Already in ipset"), tr(("Entry already in " + currentIpset).toLocal8Bit()));
	}
	else
	{
	movequery = "MOVE <%>" + currentIpset + "<%>"  + ipsetToMoveTo + "<%>" + currentIp + "<%>" + curPrimKey + "<//>";
	createConfirmChange(2);
	} 
}
void guiQIPS::moveConfirmed()
{
	nClient->netClient::sendData(movequery.toStdString());
	//updateBlockedList();

	blockTree->currentItem()->setText(4, ipsetToMoveTo );
}
QRegExpValidator * guiQIPS::getIpValidator()
{
	QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

	QRegExp ipRegex ("^" + ipRange
                 + "\\." + ipRange
                 + "\\." + ipRange
                 + "\\." + ipRange + "$");
	QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
	return ipValidator;
}
/*
	0 = Delete
	1 = Add
	2 = Move
	3 = Renew 
	If any other input is passed in, throw an error message. 
*/
void guiQIPS::createConfirmChange(int typeOfChange )
{
	confirmChangeUi * confirm = new confirmChangeUi(); 
	QString stringToDisplay = "";
	
	switch( typeOfChange )
	{
		case 0: //delete entry
			stringToDisplay = "Are you sure you want to remove entry \n" + currentIp + "\nfrom the block list?";	
			connect( confirm, SIGNAL( accepted() ), this, SLOT( removeConfirmed() ));
			break;
	
		case 1: //add new
			stringToDisplay = "Are you sure you want to block ip address " + ipToBlock + "\n and place it into ipset " + ipsetToMoveTo + "?";
			connect( confirm, SIGNAL( accepted()), this, SLOT( blockConfirmed() ));
			confirm->setWindowTitle("Confirm Block");
			break;
		case 2: //move entry
			stringToDisplay = "Are you sure you want to move entry \n" + currentIp + "\nfrom ipset  " + currentIpset + " to ipset " + ipsetToMoveTo + "?";
			connect( confirm, SIGNAL( accepted()), this, SLOT( moveConfirmed() ));		
			confirm->setWindowTitle("Confirm Move");
			break;
		case 3: //renew entry
			stringToDisplay = "Are you sure you want to renew entry \n" + currentIp + "?";	
			connect( confirm, SIGNAL(accepted()), this, SLOT( renewConfirmed() ));
			confirm->setWindowTitle("Confirm Renew");	
			break;
		default: //unknown change int.
			QMessageBox::critical( this, tr("Error"), tr("Unknown change type passed in." ));
			break;
	
	}
	confirm->confirmQuestion->setText(stringToDisplay);	
	confirm->exec();
}	
void guiQIPS::searchForEntry()
{
	QList<QTreeWidgetItem*> entry = blockTree->findItems( searchLineEdit->text() , Qt::MatchContains, 1 );
	if( entry.size() == 0 )
	{
		QString errormsg = searchLineEdit->text() + " is not in the block list.";
		QMessageBox::warning( this, tr("Not found"), tr(errormsg.toLocal8Bit()));
	}
	else
	{
		blockTree->setCurrentItem( entry[0], 1, QItemSelectionModel::Select );
	}
	
}
void guiQIPS::reportErrors()
{	
	QString errormsg = "Could not refresh due to the following: ";
	errormsg += nClient->errorString();
	QMessageBox::critical( this, tr("Error Connecting To Server"), tr(errormsg.toLocal8Bit()));	
	refresh->stop();

}
void guiQIPS::updateBlockedList()
{
	
	newEntries = 0;
	delete nClient;
	nClient = new netClient;
	connect( nClient, SIGNAL( error(QAbstractSocket::SocketError)), this, SLOT( reportErrors()));
	nClient->hostConnect();
	connect( nClient, SIGNAL( connected()), this, SLOT(  connectedToServer()));	
	refresh->start(refreshInterval);


}
void guiQIPS::connectedToServer()
{
	connect( nClient, SIGNAL( sentReply( std::string )), this, SLOT (processServerReply(std::string)) );
	//blockTree->clear();
	if( first == 0 )
	{
		nClient->netClient::sendData("getallblocked<&&>first<//>");	
		first++;	
	}
	else
	{
		//qWarning()<<"sent command";
		nClient->netClient::sendData("getallblocked<&&>"+ recentTime.toString("yyyy-MM-dd HH:mm:ss").toStdString() +"<//>");	
	}
}
void guiQIPS::processServerReply( std::string reply )
{
	QString qReply = QString::fromStdString(reply );

	if( qReply.contains("<***>"))
	{
		ipsetStats->clear();
		//Reply contains stats; parse through and update stats.
		QString stats = qReply.section("<***>", -1);
		unh = stats.section(".", 0,0).toInt();
		//ipsetStats->setText(QString::fromStdString("UNH: " + to_string(unh)) );
		ipsetStats->append(QString("UNH: %1").arg(unh) );
		
		spamhaus = qReply.section(".", 1,1).toInt();
		//ipsetStats->append(QString::fromStdString("spamhaus: " + to_string(spamhaus)) );
		ipsetStats->append(QString("spamhaus: %1").arg(spamhaus) );
		
		honeypot = qReply.section(".", 2,2).toInt();
		//ipsetStats->append(QString::fromStdString("honeypot: " + to_string(honeypot)) );
		ipsetStats->append(QString("honeypot: %1").arg(honeypot) );

		totEntries = unh + spamhaus + honeypot;
		//qWarning()<<"The total number of entries is " << totEntries;

		
	}
	else if( qReply.contains("already exists"))
	{
		QMessageBox::critical( this, tr("Error"), tr("That address already exists in that ipset."));
	}
	else if( qReply.contains("Cannot"))
	{
				
		QMessageBox::critical( this, tr("Error"), tr(qReply.toLocal8Bit()));
	
	}
	else if( qReply.contains("done"))
	{
		updateBlockedList();
		//qWarning()<<"done";
	}
	else if( qReply.contains("first"))
	{
		
		QString id = qReply.section( "<!!>", -1 );
		qReply = qReply.section( "<!!>", 0, 0 );
		qReply = qReply.section( "first", 1, 1 );
		QString timestamp = qReply.section("|", 0, 0);
		QString ipadd = qReply.section("|", 1, 1);
		QString reporter = qReply.section("|", 2, 2);
		QString process = qReply.section("|", 3, 3 );
		QString theipset = qReply.section("|", 4, 4 );
		QString description = qReply.section("|", 5, 5);
		QString deleteFlag = qReply.section("|", 6, 6 );
		
		if( deleteFlag.toInt() == 0 )
		{
		
			QTreeWidgetItem *i = new QTreeWidgetItem(blockTree);
					
			i->setText( 0, tr(timestamp.toLocal8Bit()) );	
			i->setText( 1, tr(ipadd.toLocal8Bit()) );
			i->setText( 2, tr(reporter.toLocal8Bit()) );
			i->setText( 3, tr(process.toLocal8Bit()) );
			i->setText( 4, tr(theipset.toLocal8Bit()) );
			i->setText( 5, tr(description.toLocal8Bit()) );
			
			for( int col = 0; col <= 5; col++ )
			{
				i->setData( col, Qt::UserRole, id );
			}
		}
		numOfItems++;
		//qWarning()<<"The num of items is " << numOfItems;
		//qWarning()<< "Cur pos: " <<  blockTree->verticalScrollBar()->value() << " Max pos: " << blockTree->verticalScrollBar()->maximum();
		if(numOfItems == totEntries)
		{
			blockTree->scrollToBottom();
		
		}

 	}
	else
	{
	
		QString id = qReply.section( "<!!>", -1 );
		qReply = qReply.section( "<!!>", 0, 0 );
		QString timestamp = qReply.section("|", 0, 0);
		QString ipadd = qReply.section("|", 1, 1);
		QString reporter = qReply.section("|", 2, 2);
		QString process = qReply.section("|", 3, 3 );
		QString theipset = qReply.section("|", 4, 4 );
		QString description = qReply.section("|", 5, 5);
		QString deleteFlag = qReply.section("|", 6, 6 );
	
		//qWarning()<< "Recent time before update: " << recentTime;
		//qWarning()<< "The timestamp of this entry is: " << timestamp;
	 
		QList<QTreeWidgetItem*> entry = blockTree->findItems( ipadd , Qt::MatchContains, 1 );
	
		if( entry.size() != 0 )
		{
			for( int i = 0; i < entry.size(); i++)
			{		
				if( deleteFlag.toInt() == 1 )
				{	
					//qWarning()<< "deleted entry found";
					delete entry.at(i);
					numOfItems--;
				}
			}
		}
		else
		{	
			if( deleteFlag.toInt() == 0 )
			{
				//qWarning()<< deleteFlag;
				//qWarning()<< qReply;
				//qWarning()<< "delete flag is 0";
				bool atBot = false;
				if( blockTree->verticalScrollBar()->value() ==  blockTree->verticalScrollBar()->maximum() )
				{
					atBot = true;
				}
				newEntries++;
				QTreeWidgetItem *i = new QTreeWidgetItem(blockTree);
				
				i->setText( 0, tr(timestamp.toLocal8Bit()) );	
				i->setText( 1, tr(ipadd.toLocal8Bit()) );
				i->setText( 2, tr(reporter.toLocal8Bit()) );
				i->setText( 3, tr(process.toLocal8Bit()) );
				i->setText( 4, tr(theipset.toLocal8Bit()) );
				i->setText( 5, tr(description.toLocal8Bit()) );
				
				for( int col = 0; col <= 5; col++ )
				{
					i->setData( col, Qt::UserRole, id );
				}
				numOfItems++;
				if( atBot == true )
				{
					blockTree->scrollToBottom();
				}
			
			}
			
		}
	
		
	
	}
	
	//blockTree->verticalScrollBar()->setSliderPosition(blockTree->verticalScrollBar()->maximum() + 500);
	recentTime = QDateTime::currentDateTime();
	//qWarning()<< "Recent time after update:" << recentTime;
}
void guiQIPS::updateStats( )
{
	nClient->netClient::sendData("updatestat<//>");
} 



