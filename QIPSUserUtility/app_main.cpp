#include <stdlib.h>
#include <stdio.h>
#include <qips_utility.h>
#include <QCoreApplication>
#include <QObject>

using namespace std;
#define __MAIN__

int main(int argc, char ** argv)
{
	QCoreApplication a(argc, argv);  
	QCoreApplication::setOrganizationName("RCC");
	QCoreApplication::setOrganizationDomain("sr.unh.edu");
	QCoreApplication::setApplicationName("Barricade");

	string usage = "Usage:\n ./utility: Normal user creation mode. \n ./utility -l: View list of all users and whether or not they are admininstrators. \n ./utility -d <username>: Delete a given user in administrative mode. \n ./utility -a <username>: Make a given user an administrator in administrative mode." ;
	QIPSUtility u;
	if( argc == 1 )
	{
		u.setMode(0);
	}
	else if( argc == 2 )
	{
		if( string(argv[1]) != "-l" )
		{
			cout<< usage <<endl;
			exit(1);
		}
		else
		{
			u.setMode(3);
			
		}
	}
	else if( argc == 3 )
	{
		if( string(argv[1]) != "-d" && string(argv[1]) != "-a" )
		{
			cout<< usage <<endl;
			exit(1);
		}
		else
		{
			if(string(argv[1]) == "-d" )
			{
				u.setMode(1);
				u.setUser(QString::fromStdString(string(argv[2])));
			}
			else
			{
				u.setMode(2);
				u.setUser(QString::fromStdString(string(argv[2])));
			}
		}
	}
	else
	{
	cout<< usage <<endl;
	exit(1);
	}
	u.connectToServer();
	a.exec(); 

	exit(0);
}
