#include "testwindow.h"
#include <QtWidgets>


//TestWindow::TestWindow(ISMRTDev *pDev, QWidget *parent)
//	: QWidget(parent)
//	, IDev(pDev)
TestWindow::TestWindow(QWidget* parent)
	: QWidget(parent)
{
/*
	QVBoxLayout *pVBox = new QVBoxLayout;

	pVBox->addWidget(createGroupCtrl());
	pVBox->addWidget(createGroupTest());
	pVBox->addStretch(1);

	setLayout(pVBox);
	//resize(TEST_WINDOW_WIDTH,TEST_WINDOW_HEIGHT);

	//SignalSlot s1;
	QObject::connect(nullptr, SIGNAL(btn_enabled(int)), this, SLOT(btn_enable(int)));
	*/
}

