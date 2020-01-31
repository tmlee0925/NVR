#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QtWidgets>


//MainWindow::MainWindow(ISMRTDev *pDev, QWidget *parent)
//    : QWidget(parent)
//	, IDev(pDev)
MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
{
/*	if (pDev == nullptr)
	{
		printf("can't not find device info\n");
		return;
	}

	if (pDev->getOperMode() == ISMRTDev::OM_MONITORING)
	{
		setWindowTitle(tr("COP - Monitoring Mode"));
		DWORD dwIP = pDev->getMonIP();

		printf("Monitoring IP %s", inet_ntoa(*(in_addr *)&dwIP));


	}
	else if (pDev->getOperMode() == ISMRTDev::OM_EMULATING)
	{
		setWindowTitle(tr("MCB - Emulating Mode"));
		DWORD dwIP = pDev->getIP();
		printf("Local IP %s", inet_ntoa(*(in_addr *)&dwIP));
	}
	else
	{
		setWindowTitle(tr("MCB - Normal Mode"));
		DWORD dwIP = pDev->getIP();
		printf("Local IP %s", inet_ntoa(*(in_addr *)&dwIP));
	}

	
		QHBoxLayout *mainLayout = new QHBoxLayout;
		DevWindow *pDevWnd = new DevWindow(pDev, this);
		TestWindow *pTestWnd = new TestWindow(pDev, this);

		mainLayout->addWidget(pDevWnd);
		mainLayout->addWidget(pTestWnd);
		mainLayout->addStretch();
		setLayout(mainLayout);
	*/
}
