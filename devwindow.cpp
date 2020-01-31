#include "devwindow.h"
#include <QtWidgets>

//DevWindow::DevWindow(ISMRTDev *pDev, QWidget *parent)
//	: QWidget(parent)
//	, IDev(pDev)
DevWindow::DevWindow(QWidget* parent)
    : QWidget(parent)
{
    Q_UNUSED(parent);

    /*


    QHBoxLayout *mainLayout = new QHBoxLayout;
    DevTab *pDevTab = new DevTab(this);
    TestTab *pTestTab = new TestTab(this);
    //mainLayout->add(pDevTab);
    //mainLayout->addLayout(pTestTab);
    mainLayout->addWidget(pDevTab);
    mainLayout->addWidget(pTestTab);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
*/

    /*tabWidget = new QTabWidget;
    tabWidget->addTab(new DevTab(), tr("Device"));
    tabWidget->addTab(new TestTab(), tr("Test"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);


*/
    //update_background();
    //setWindowTitle("Custom Widget");
    //setStyleSheet("border-image:url(:/resources/cop.png)");
    //setStyleSheet("border-image:url(d:\\cop.png)");

/*
    //QPixmap bg(":/resources/cop.png");
    QPixmap bg(":/resources/cop.png");
    QPalette p(palette());
    p.setBrush(QPalette::Background, bg);
    setAutoFillBackground(true);
    setPalette(p);
  */

   /* QLabel *fileNameLabel = new QLabel(tr("File Name:"));
    QLineEdit *fileNameEdit = new QLineEdit(tr("File Info:"));

    QLabel *pathLabel = new QLabel(tr("Path:"));
    QLabel *pathValueLabel = new QLabel(tr("File Path:"));
    pathValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(fileNameEdit);
    mainLayout->addWidget(pathLabel);
    mainLayout->addWidget(pathValueLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
*/
    QLabel *img = new QLabel(this);
    m_BG = QPixmap("./data/mcb.png");
    img->setPixmap(m_BG);
    img->show();
QString sPath = QCoreApplication::applicationDirPath();
   qDebug() << "ptah=" << sPath;
    setFixedSize(m_BG.size());

    //QSize s = img->size();
    //m_BG = m_BG.scaled(size(), Qt::IgnoreAspectRatio);


    //img->setAttribute(Qt::WA_DeleteOnClose);

}


void DevWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);




}



void DevWindow::update_background()
{
    //m_BG = QPixmap("d:\\cop.png");
    m_BG = QPixmap(":/mcb.png");
    /*QBitmap bitmap = m_device.createHeuristicMask();
    setFixedSize(m_device.size());
    setMask(bitmap);
    */


    //m_device = m_device.scaled(w.size(), Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Background, m_BG);
    setPalette(palette);
    //int _w = w.width();
    //int h = w.height();



    //QPixmap bg("d:\\cop.png");
    setFixedSize(m_BG.size());
    //m_BG = m_BG.scaled(size(), Qt::IgnoreAspectRatio);

    QPalette p;
    p.setBrush(QPalette::Background, m_BG);
    setPalette(p);

    update();




}




