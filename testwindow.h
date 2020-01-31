#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
//#include "ISMRTDev.h"

/*#include "iowindow.h"
#include "memorywindow.h"
#include "videowindow.h"
#include "audiowindow.h"
#include "serialwindow.h"
#include "filewindow.h"
#include "networkwindow.h"
*/
class TestWindow : public QWidget//, public IDev
{
	Q_OBJECT
public:
	//TestWindow(ISMRTDev * pDev, QWidget * parent = nullptr );
	TestWindow(QWidget* parent = nullptr);

	QGroupBox *     createGroupCtrl();
	QGroupBox *     createGroupTest();
	QPushButton*    createBtn(const QString &text);
	void            btnCtrlClicked();
	void            btnTestClicked();

private:
	QList<QPushButton*> listBtnCtrl;
    // IO
    // Memory
    // Video
    // Audio
    // Serial
    // File
    // Network
	QPushButton *pBtnTest;
    
};

#endif // TESTWINDOW_H
