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
	refresh = new QTimer(this);
	connect( refresh, SIGNAL(timeout()), this, SLOT(updateBlockedList()));
	refresh->start(refreshInterval);

 
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
		ipsetToMoveTo = blockIpset->currentItem()->text();
		blockquery = "block entry," + ipToBlock + ",in ipset," + ipsetToMoveTo + "<//>";
		guiQIPS::createConfirmChange(1);
	} 
}
void guiQIPS::blockConfirmed()
{
	if( nClient == NULL )
	{
		guiQIPS::updateBlockedList();
	}

	nClient->netClient::sendData(blockquery.toStdString());

	QTreeWidgetItem *i = new QTreeWidgetItem(blockTree);
	
	i->setText( 0, tr( QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").toLocal8Bit() ));	
	i->setText( 1, tr(ipToBlock.toLocal8Bit()));
	i->setText( 2, tr("User"));
	i->setText( 3, tr("User"));
	i->setText( 4, tr(ipsetToMoveTo.toLocal8Bit()));
	i->setText( 5, tr(""));
	blockTree->verticalScrollBar()->setSliderPosition( blockTree->verticalScrollBar()->value() - 5);
	updateStats("user-defined", 1); //Let's use "user-defined" for now because it is from a statistic that is not counted.
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
	blockTree->currentItem()->setText(0,  QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
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
	QString delstat = blockTree->currentItem()->text(4);
	updateStats( delstat, 0 );
	delete blockTree->currentItem();
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
	QString old = blockTree->currentItem()->text(4);	
	updateStats( old, 1 );
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

}
void guiQIPS::updateBlockedList()
{
	newEntries = 0;
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
		nClient->netClient::sendData("getallblocked<&&>"+ recentTime.toString("yyyy-MM-dd HH:mm:ss").toStdString() +"<//>");	
	}
}
void guiQIPS::processServerReply( std::string reply )
{
	

	QString qReply = QString::fromStdString(reply );
	if( qReply.contains("<***>"))
	{
		//Reply contains stats; parse through and update stats.
		QString stats = qReply.section("<***>", -1);
		unh = stats.section(".", 0,0).toInt();
		ipsetStats->setText(QString::fromStdString("UNH: " + to_string(unh)) );
		
		spamhaus = qReply.section(".", 1,1).toInt();
		ipsetStats->append(QString::fromStdString("spamhaus: " + to_string(spamhaus)) );
		
		honeypot = qReply.section(".", 2,2).toInt();
		ipsetStats->append(QString::fromStdString("honeypot: " + to_string(honeypot)) );
		
	}
	else if( qReply.contains("already exists"))
	{
		QMessageBox::critical( this, tr("Error"), tr("That address already exists in that ipset."));
	}
	else if( qReply.contains("Cannot"))
	{
			
			QMessageBox::critical( this, tr("Error"), tr(qReply.toLocal8Bit()));
			QList<QTreeWidgetItem*> entry = blockTree->findItems( ipToBlock , Qt::MatchContains, 1 );
			delete entry[0];
	

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
	 
		QList<QTreeWidgetItem*> entry = blockTree->findItems( ipadd , Qt::MatchContains, 1 );

		if( entry.size() != 0 )
		{
			//Entry was added from your client without refreshing, so delete the extra entry.
			for( int i = 0; i < entry.size(); i++)
			{		
				delete entry.at(i);
				
			}
		}
		else
		{	//A different client entered an entry, so update the new entry count.
			newEntries++;
		}
	
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
		recentTime = QDateTime::currentDateTime();
		//qWarning()<<recentTime.toString("ddd MMM d h:mm:ss yyyy");
	} 

			//qWarning()<<newEntries;
			blockTree->verticalScrollBar()->setSliderPosition( blockTree->verticalScrollBar()->value() - (newEntries * 2));
			//qWarning()<<blockTree->verticalScrollBar()->maximum();
 
		
	
}
void guiQIPS::updateStats( QString oldipset, int operation )
{
	
	if( operation == 0 ) //delete IP address
	{
		if( QString::compare( oldipset, "unh") == 0 )
		{
			unh--;

		}
		else if(QString::compare( oldipset,  "spamhaus") == 0 )
		{
			spamhaus--;


		}
		else if( QString::compare( oldipset, "honeypot") == 0 )
		{
			honeypot--;
		
		}	
	}
	else //move or add ip
	{
		if( QString::compare( oldipset, "unh") == 0 )
		{
			unh--;

			if(  QString::compare( ipsetToMoveTo, "spamhaus") == 0 )
			{
				spamhaus++;
			}
			else if( QString::compare( ipsetToMoveTo, "honeypot") == 0 )
			{	
				honeypot++;
			}

		}
		else if(QString::compare( oldipset,  "spamhaus") == 0 )
		{
			spamhaus--;

			if( QString::compare(ipsetToMoveTo, "honeypot") == 0 )
			{
				honeypot++;

			}
			else if( QString::compare(ipsetToMoveTo, "unh" ) == 0 )
			{
				unh++;
			}

		}
		else if( QString::compare( oldipset, "honeypot") == 0 )
		{
			honeypot--;

			if( QString::compare( ipsetToMoveTo, "spamhaus") == 0 )
			{
				spamhaus++;
			}
			else if( QString::compare( ipsetToMoveTo, "unh") == 0 )
			{
				unh++;
			
			}
		
		}
		else if( QString::compare( oldipset,  "user-defined") == 0 ) //Also used for adding new IPs
		{
			//user-defined is not logged so no subtraction in this version. 

			if( QString::compare( ipsetToMoveTo, "spamhaus") == 0 )
			{
				spamhaus++;
			}
			else if( QString::compare( ipsetToMoveTo, "unh") == 0 )
			{
				unh++;
			}
			else if( QString::compare( ipsetToMoveTo, "honeypot" ) == 0 )
			{
				honeypot++;
			
			}
		}
	}
	ipsetStats->setText(QString::fromStdString("UNH: " + to_string(unh)) );
	ipsetStats->append(QString::fromStdString("spamhaus: " + to_string(spamhaus)) );
	ipsetStats->append(QString::fromStdString("honeypot: " + to_string(honeypot)) );

}



