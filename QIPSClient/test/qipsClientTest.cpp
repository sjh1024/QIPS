#include <QtTest/QtTest>
#include <qipsClientTest.h>
Q_DECLARE_METATYPE(std::string);
/*void qipsClientTest::blockUserDefinedAddsIPToCorrectIpset()
{
	QSqlDatabase ips = QSqlDatabase::addDatabase("QSQLITE");
	ips.setDatabaseName("/usr/local/honeypot/bin/db/qips.db");
	ips.open();		
	guiQIPS test;
	QTest::mouseClick(test.refreshButton, Qt::LeftButton );
	QTest::keyClicks(test.blockEntry, "20.9.22.98");
	test.blockIpset->setCurrentItem(test.blockIpset->item(0));
	QTest::mouseClick(test.submitBlock, Qt::LeftButton );
	QTest::qSleep(1000);
	//make sure ip add to db is successful
	QSqlQuery query("SELECT * FROM ipset WHERE ipset = 'user-defined' AND ipaddress = '20.9.22.98'");
	QCOMPARE( query.next(), true );
	//make sure ip add to ipset is successful
	QProcess *testIpset = new QProcess();
	testIpset->start( "sudo", QStringList() << "/usr/sbin/ipset" << "test" << "user-defined" << "20.9.22.98" );
	testIpset->waitForFinished();	
	QCOMPARE( testIpset->exitCode(), 0 );
	//delete the ip address
	QSqlQuery del("DELETE FROM ipset WHERE ipset = 'user-defined' AND ipaddress = '20.9.22.98'");
	QProcess *delIpset = new QProcess();
	delIpset->start( "sudo", QStringList() << "/usr/sbin/ipset" << "-D" << "user-defined" << "20.9.22.98");
	
}
void qipsClientTest::blockUnhAddsIPToCorrectIpset()
{
		
	guiQIPS test;

	qRegisterMetaType<std::string>();
	QTest::mouseClick(test.refreshButton, Qt::LeftButton );
	QTest::keyClicks(test.blockEntry, "20.9.22.98");
	test.blockIpset->setCurrentItem(test.blockIpset->item(1));
	QTest::mouseClick(test.submitBlock, Qt::LeftButton );
	QTest::qSleep(1000);
	//make sure ip add to db is successful
	QSqlQuery query("SELECT * FROM ipset WHERE ipset = 'unh' AND ipaddress = '20.9.22.98'");
	QCOMPARE( query.next(), true );
	//make sure ip add to ipset is successful
	QProcess *testIpset = new QProcess();
	testIpset->start( "sudo", QStringList() << "/usr/sbin/ipset" << "test" << "unh"  << "20.9.22.98" );
	testIpset->waitForFinished();	
	QCOMPARE( testIpset->exitCode(), 0 );
	//delete the ip address
	QSqlQuery del("DELETE FROM ipset WHERE ipset = 'unh' AND ipaddress = '20.9.22.98'");
	QProcess *delIpset = new QProcess();
	delIpset->start( "sudo", QStringList() << "/usr/sbin/ipset" << "-D" << "unh" << "20.9.22.98");
	
}
void qipsClientTest::blockHoneypotAddsIPToCorrectIpset()
{
	guiQIPS test;
	QTest::mouseClick(test.refreshButton, Qt::LeftButton );
	QTest::keyClicks(test.blockEntry, "20.9.22.98");
	test.blockIpset->setCurrentItem(test.blockIpset->item(2));
	QTest::mouseClick(test.submitBlock, Qt::LeftButton );
	QTest::qSleep(1000);
	//make sure ip add to db is successful
	QSqlQuery query("SELECT * FROM ipset WHERE ipset = 'honeypot' AND ipaddress = '20.9.22.98'");
	QCOMPARE( query.next(), true );
	//make sure ip add to ipset is successful
	QProcess *testIpset = new QProcess();
	testIpset->start( "sudo", QStringList() << "/usr/sbin/ipset" << "test" << "honeypot"  << "20.9.22.98" );
	testIpset->waitForFinished();
	QCOMPARE( testIpset->exitCode(), 0 );
	//delete the ip address
	QSqlQuery del("DELETE FROM ipset WHERE ipset = 'honeypot' AND ipaddress = '20.9.22.98'");
	QProcess *delIpset = new QProcess();
	delIpset->start( "sudo", QStringList() << "/usr/sbin/ipset" << "-D" << "honeypot" << "20.9.22.98");
}
void qipsClientTest::blockSpamhausAddsIPToCorrectIpset()
{
	guiQIPS test;
	QTest::mouseClick(test.refreshButton, Qt::LeftButton );
	QTest::keyClicks(test.blockEntry, "20.9.22.98");
	test.blockIpset->setCurrentItem(test.blockIpset->item(3));
	QTest::mouseClick(test.submitBlock, Qt::LeftButton );
	QTest::qSleep(1000);
	//make sure ip add to db is successful
	QSqlQuery query("SELECT * FROM ipset WHERE ipset = 'spamhaus' AND ipaddress = '20.9.22.98'");
	QCOMPARE( query.next(), true );
	//make sure ip add to ipset is successful
	QProcess *testIpset = new QProcess();
	testIpset->start( "sudo", QStringList() << "/usr/sbin/ipset" << "test" << "spamhaus"  << "20.9.22.98" );
	testIpset->waitForFinished();
	QCOMPARE( testIpset->exitCode(), 0 );
	//DON'T DELETE THE IP; will be using it for the next tests.
}
void qipsClientTest::moveEntryMovesSpamhausToHoneypot()
{
	//guiQIPS test;
	//QTest::mouseClick(test.refreshButton, Qt::LeftButton );
	//test.blockTree->setCurrentItem(test.blockTree->topLevelItem(0));
	//test.moveEntry();
	//make sure ip move in db (new "ipset" field value is correct) is successful
	//ip is gone from old ipset
	//ip exists in new ipset
	//test that stat changes
	//delete ip address
	//QSKIP("Menu item; need to learn how to test this");
}
void qipsClientTest::renewEntryRenewsEntryToCorrectRenewalTime()
{
	//make sure server is running
	//add new ip, confirm that it's in ipset
	//save the current ipset's remaining time
	//renew ip address
	//check if it's in correct ipset (since you have to do a removal and readd)
	//Check if the ipset's remaining time is greater than that of the old remaining time
	//delete the ip address
	//QSKIP("Menu item; need to learn how to test this");
} */
void qipsClientTest::refreshIntervalCorrectOnNoAction()
{
	//Start Client, and a timer
	guiQIPS test;
	qRegisterMetaType<std::string>("std::string");
	QTest::mouseClick(test.refreshButton, Qt::LeftButton );
	QSignalSpy spy(test.nClient, SIGNAL(sentReply(std::string)));
	QTest::qWait(50000);
	//Wait for 30 seconds. Don't take any action.
	//Use QSignalSpy to check if net_client's "sentReply" signal was received exactly once.
	QCOMPARE( spy.count(), 1 );
}
void qipsClientTest::refreshIntervalCorrectOnNewSubmit()
{
	//Start Client, and a timer
	//Wait for 20 seconds.
	//Refresh.
	//Wait 15 seconds.
	//Use QSignalSpy to check if net_client's "sentReply" signal was received exactly once; confirms the refresh did not occur again. 
}
//void qipsClientTest::refreshIntervalCorrectOnUIAction()
void qipsClientTest::addingWhitelistIPsResultsInFailure()
{
	//make sure server is running
	//For each IP address whitelist "type"...
		//Attempt to submit it
		//Make sure that it does not end up in the database
		//Make sure that it does not end up in ipset
		//Make sure that the exit code is correct.
	
}
void qipsClientTest::scrollValuesChangeCorrectlyOnRefreshWithNoNewVals()
{
	//make sure server is running
	//Refresh
	//Make sure the scroll value did not change
}
void qipsClientTest::scrollValuesChangeCorrectlyOnNewEntry()
{
	//make sure server is running
	//Submit a new address
	//Ensure that the scrollbar moves up exactly (20?) steps from its previous position.
}
void qipsClientTest::addingDuplicateAddressResultsInFailure()
{
	//make sure server is running
	//submit a new address
	//confirm it's in the database and ipset
	//try to add the same exact address to the same exact ipset
	//confirm it didn't get added to the db by taking a count of entries with that ip/ipset
	//**IPSET WILL NOT ADD DUPLICATE ADDRESSES. NO NEED TO TEST IT**
}
void qipsClientTest::addingMultipleAddressesResultsInCorrectNumOfEntries()
{
}
void qipsClientTest::statsUpdatedCorrectly()
{
	//Add three special IPs to the block list, each in their own ipset.
	//Confirm that the stats were updated appropriately.
	//Move each one to a different ipset.
	//Confirm that the stats were updated appropriately.
	//Delete all three ips.
	//Confirm the stats were all updated appropriately.
}
//void qipsClientTest::entriesLoadedAreOnlyWithin24Hours()
QTEST_MAIN( qipsClientTest )

