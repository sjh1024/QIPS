#include <QWidget>
#include <QMessageBox>
#include<ui_confirmChange.h>


#ifndef CONFIRMCHANGE
#define CONFIRMCHANGE
class confirmChangeUi : public QDialog, public Ui::confirmChangeBox
{ 
	Q_OBJECT 

public:
	confirmChangeUi(QWidget * parent = 0 );
	

private:

public slots:

signals:

};

#endif
