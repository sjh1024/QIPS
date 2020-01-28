#include <stdlib.h>
#include <stdio.h>
#include <gui_QIPS.h>
#include <QApplication>
#include <QObject>
#include <QClipboard>
#include <gui_login.h>

#define __MAIN__

int main(int argc, char ** argv)
{

  QApplication a(argc, argv);

  QApplication::setOrganizationName("RCC");
  QApplication::setOrganizationDomain("sr.unh.edu");
  QApplication::setApplicationName("Barricade");

  qipsLoginUi l;
  l.exec();

  exit(0);
}
