#ifndef DEVWINDOW_H
#define DEVWINDOW_H

#include <QWidget>
//#include "ISMRTDev.h"


class DevWindow : public QWidget//, public IDev
{
    Q_OBJECT
public:
	//explicit  DevWindow(ISMRTDev *pDev, QWidget *parent = nullptr);
    explicit  DevWindow(QWidget* parent = nullptr);

private:
    int w_width;
    int w_height;
    QPixmap m_BG;
    //QTabWidget *tabWidget;
    //QDialogButtonBox *buttonBox;

protected:
    void update_background();

protected:
    virtual void paintEvent(QPaintEvent *event);

};

#endif // DEVWINDOW_H
