#include <stdlib.h>
#include <stdio.h>
#include <net_server.h>
#include <QCoreApplication>
#include <QObject>

#define __MAIN__

int main(int argc, char ** argv)
{

  QCoreApplication a(argc, argv);

  QCoreApplication::setOrganizationName("RCC");
  QCoreApplication::setOrganizationDomain("sr.unh.edu");
  QCoreApplication::setApplicationName("Barricade");
  
  printf("Creating server...\n");
  netServer ns(4998);
  a.exec();
  //exit(0);
}
