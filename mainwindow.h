#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "devwindow.h"
#include "testwindow.h"
//#include "ISMRTDev.h"


class MainWindow : public QWidget//, public IDev
{
    Q_OBJECT

public:
    //explicit MainWindow(QWidget *parent = nullptr);
	//MainWindow(ISMRTDev *pDev = nullptr, QWidget *parent = nullptr);
    MainWindow(QWidget* parent = nullptr);
protected:


private:
    DevWindow	*m_pDev;
    TestWindow	*m_pTest;
};

#endif // MAINWINDOW_H
