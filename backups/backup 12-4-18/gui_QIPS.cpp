#include<gui_QIPS.h>
#include<gui_confirmChange.h>
#include<QTimer>
using namespace std;
guiQIPS::guiQIPS(QWidget * parent)
:QDialog( parent )
{
	setupUi( this );
	this->blockTree->viewport()->installEventFilter(this);
	blockTree->blockSignals(false);
	//Connect button clicks to respective slots 
	connect(refreshButton, SIGNAL( clicked() ), this, SLOT( updateBlockedList() ) );
	connect(submitBlock, SIGNAL( clicked() ), this, SLOT(blockNewIp()));
	connect(searchButton, SIGNAL( clicked() ), this, SLOT( searchForEntry()));

	//Change the column widths so you can see everything
	blockTree->setColumnWidth(0, 200 );
	blockTree->setColumnWidth(1, 150 );
	blockTree->setColumnWidth(3, 250 );
	
	//setValidators.
	QRegExpValidator *ipValidator = guiQIPS::getIpValidator();
	blockEntry->setValidator(ipValidator);
	searchLineEdit->setValidator(ipValidator);
	
	//Refresh every 30 seconds
	QTimer *refresh = new QTimer(this);
	connect( refresh, SIGNAL(timeout()), this, SLOT(updateBlockedList()));
	refresh->start(30000);

 
}
bool guiQIPS::eventFilter(QObject *obj, QEvent *event)
{
	if( obj == blockTree->viewport() )
    	{
   		if( event->type() == QEvent::MouseButtonPress )
    		{
		
			QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);

    			if (MouseEvent->button() == Qt::RightButton ) 
			{
       			
				if(blockTree->itemAt(MouseEvent->pos()))
				{
					QPoint p = MouseEvent->pos();
					blockTree->setCurrentItem( blockTree->itemAt(MouseEvent->pos()));
					//create right click menu
					QMenu *entryOptions =  new QMenu(this);
					QAction *renew = new QAction( "Renew" );
					connect( renew, SIGNAL( triggered()), this, SLOT( renewEntry() ));
					QAction *remove = new QAction( "Remove" );
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
	currentIpset = blockIpset->currentItem()->text();
	blockquery = "block entry," + ipToBlock + ",in ipset," + currentIpset + "<//>";
	
	} 
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

	if(typeOfChange == 0 )//delete
	{
	}
	else if( typeOfChange == 1 )//add new
	{	
		stringToDisplay = "Are you sure you want to block ip address " + ipToBlock + "\n and place it into ipset " + currentIpset + "?";
		connect( confirm, SIGNAL( accepted()), this, SLOT( blockConfirmed() ));
		confirm->setWindowTitle("Confirm Block");
	}
	else if( typeOfChange == 2 ) //move
	{
		QString stringToDisplay = "Are you sure you want to move entry \n" + currentIp + "\nfrom ipset  " + currentIpset + " to ipset " + ipsetToMoveTo + "?";
		connect( confirm, SIGNAL( accepted()), this, SLOT( moveConfirmed() ));		
		confirm->setWindowTitle("Confirm Move");
	
	}
	else if( typeOfChange == 3 ) // renew
	{
	}
	else // invalid input, throw error
	{
		QMessageBox::critical( this, tr("Error"), tr("Unknown change type passed in." ));
		return;
	}
	confirm->confirmQuestion->setText(stringToDisplay);
	
	confirm->exec();
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
	blockTree->clear();
	nClient->netClient::sendData("getallblocked<//>");
	
}
void guiQIPS::processServerReply( std::string reply )
{
	
	
	QString qReply = QString::fromStdString(reply );
	if( qReply.contains("<***>"))
	{
		QString stats = qReply.section("<***>", -1);
		unh = stats.section(".", 1,1).toInt();
		ipsetStats->setText(QString::fromStdString("UNH: " + to_string(unh)) );
		
		spamhaus = qReply.section(".", 2,2).toInt();
		ipsetStats->append(QString::fromStdString("spamhaus: " + to_string(spamhaus)) );
		
		honeypot = qReply.section(".", 3,3).toInt();
		ipsetStats->append(QString::fromStdString("honeypot: " + to_string(honeypot)) );
		
	}
	else if( qReply.contains("already exists"))
	{
		QMessageBox::critical( this, tr("Error"), tr("That address already exists in that ipset."));
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
 
	///Create the TreeWidgetItem
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
	
	
}
void guiQIPS::renewEntry()
{
	QString primkey = blockTree->currentItem()->data(0, Qt::UserRole).toString();
	QString ipadd = blockTree->currentItem()->text(1);
	QString ipset = blockTree->currentItem()->text(4);

	renewquery = "Renew<%>" + ipset + "<%>" + ipadd + "<%>" + primkey + "<//>";
	
	confirmChangeUi * confirm = new confirmChangeUi();
	connect( confirm, SIGNAL( accepted() ), this, SLOT( renewConfirmed() ));
	QString dataToDisplay;	

	dataToDisplay += blockTree->currentItem()->text(1);

	QString stringToDisplay = "Are you sure you want to renew entry \n" + dataToDisplay + "?";	
	confirm->confirmQuestion->setText(stringToDisplay);
	confirm->setWindowTitle("Confirm Renewal");
	confirm->exec(); 
}
void guiQIPS::removeEntry(  )
{
	QString primkey = blockTree->currentItem()->data(0, Qt::UserRole).toString();
	currentIp = blockTree->currentItem()->text(1);
	QString ipset = blockTree->currentItem()->text(4);

	deletequery = "DELETE<%>" + currentIpset + "<%>" + currentIp + "<%>" + primkey + "<//>";
	confirmChangeUi *confirm = new confirmChangeUi();
	connect( confirm, SIGNAL( accepted()), this, SLOT( removeConfirmed() ));
	QString stringToDisplay = "Are you sure you want to remove entry \n" + currentIp + "\nfrom the blocklist?";	

	confirm->confirmQuestion->setText(stringToDisplay);
	confirm->setWindowTitle("Confirm Delete");
	confirm->exec(); 
	
}
void guiQIPS::blockConfirmed()
{
	nClient->netClient::sendData(blockquery.toStdString());

	QTreeWidgetItem *i = new QTreeWidgetItem(blockTree);
	
	i->setText( 0, tr( QDateTime::currentDateTime().toString().toLocal8Bit() ));	
	i->setText( 1, tr(ipToBlock.toLocal8Bit()));
	i->setText( 2, tr("User"));
	i->setText( 3, tr("User"));
	i->setText( 4, tr(currentIpset.toLocal8Bit()));
	i->setText( 5, tr(""));

	updateStats("user-defined"); //Let's use "user-defined" for now because it is from a statistic that is not counted.
	

}
void guiQIPS::removeConfirmed()
{

	nClient->netClient::sendData(deletequery.toStdString());
	delete blockTree->currentItem();

}
void guiQIPS::moveConfirmed()
{
	nClient->netClient::sendData(movequery.toStdString());
	QString old = blockTree->currentItem()->text(4);	
	updateStats( old );
	blockTree->currentItem()->setText(4, ipsetToMoveTo);
	
	
}

void guiQIPS::renewConfirmed()
{
	nClient->netClient::sendData(renewquery.toStdString());
	blockTree->currentItem()->setText(0,  QDateTime::currentDateTime().toString());
	

}
void guiQIPS::updateStats( QString oldipset )
{
	if( QString::compare( oldipset, "unh") == 0 )
	{
		unh--;

		if(  QString::compare( currentIpset, "spamhaus") == 0 )
		{
			spamhaus++;
		}
		else if( QString::compare( currentIpset, "honeypot") == 0 )
		{	
			honeypot++;
		}

	}
	else if(QString::compare( oldipset,  "spamhaus") == 0 )
	{
		spamhaus--;

		if( QString::compare(currentIpset, "honeypot") == 0 )
		{
			honeypot++;

		}
		else if( QString::compare(currentIpset, "unh" ) == 0 )
		{
			unh++;
		}

	}
	else if( QString::compare( oldipset, "honeypot") == 0 )
	{
		honeypot--;

		if( QString::compare( currentIpset, "spamhaus") == 0 )
		{
			spamhaus++;
		}
		else if( QString::compare( currentIpset, "unh") == 0 )
		{
			unh++;
		
		}
	
	}
	else if( QString::compare( oldipset,  "user-defined") == 0 )
	{
		//user-defined is not logged so no subtraction in this version. 

		if( QString::compare( currentIpset, "spamhaus") == 0 )
		{
			spamhaus++;
		}
		else if( QString::compare( currentIpset, "unh") == 0 )
		{
			unh++;
		}
		else if( QString::compare( currentIpset, "honeypot" ) == 0 )
		{
			honeypot++;
		
		}
	}
			ipsetStats->setText(QString::fromStdString("UNH: " + to_string(unh)) );
			ipsetStats->append(QString::fromStdString("spamhaus: " + to_string(spamhaus)) );
			ipsetStats->append(QString::fromStdString("honeypot: " + to_string(honeypot)) );
}
void guiQIPS::moveEntry( )
{
	ipsetToMoveTo = qobject_cast<QAction*>(sender())->text();
	QString primkey = blockTree->currentItem()->data(0, Qt::UserRole).toString();
	currentIpset = blockTree->currentItem()->text(4);

	if( QString::compare( ipsetToMoveTo, currentIpset ) == 0 )
	{
		QString errormsg = "That entry is already in ipset ";
		errormsg += currentIpset;
		QMessageBox::critical( this, tr("Already in ipset"), tr(errormsg.toLocal8Bit()));
	}
	else
	{
	movequery = "MOVE <%>" + currentIpset + "<%>"  + ipsetToMoveTo + "<%>" + currentIp + "<%>" + primkey + "<//>";

	} 
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
