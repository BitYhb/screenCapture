#include "widget.h"
#include "ui_widget.h"


#include <QThread>
#include <QScreen>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //QPalette pal(palette());
    //pal.setColor(QPalette::Background, Qt::black);
    //setAutoFillBackground(true);
    //setPalette(pal);

    startBtn = new QPushButton(this);
    stopBtn  = new QPushButton(this);
    partBtn  = new QPushButton(this);
    resize(900,900);
    qDebug() << "main thread:" <<QThread::currentThreadId();
    startBtn->setGeometry(0,0,120,60);
    stopBtn->setGeometry(300,0,120,60);
    partBtn->setGeometry(150,0,120,60);
    startBtn->setText("start");
    stopBtn->setText("stop");
    partBtn->setText("part");
    //
    s = new ScreenCaptureDialog(this);
    s->setGeometry(100,100,289,34);
//    s->raise();
    s->show();
    QObject::connect(startBtn,&QPushButton::clicked,this,&Widget::onStartBtnClicked);
    QObject::connect(stopBtn,&QPushButton::clicked,this,&Widget::onStopBtnClicked);
    QObject::connect(partBtn,&QPushButton::clicked,this,&Widget::onpartBtnClicked);
    m_screenCapThread = new ScreenCapture(this);
    partWidget = new PartArea(this);
    partWidget->setVisible(false);

    connect(partWidget,&PartArea::sigDrawRelease,this,&Widget::onSigDrawRelease);
}

Widget::~Widget()
{
    m_screenCapThread->wait();
    m_screenCapThread->quit();
}

void Widget::onStartBtnClicked()
{
    getScreenSize();
    captureInit(0,0,m_screenWidth,m_screenHeight);
    s = new ScreenCaptureDialog(this);
    s->setGeometry(100,100,289,34);
//    s->raise();
    s->show();
    //m_screenCapThread->start();
}

void Widget::onpartBtnClicked()
{
    qDebug() << "do part";
    partWidget->setVisible(true);
}

void Widget::onSigDrawRelease(const QRect rect)
{
    captureInit(rect.x(),rect.y(),rect.width(),rect.height());
    m_screenCapThread->start();
}

void Widget::captureInit(const int offsetX, const int offsetY, const int width, const int height)
{
    m_screenCapThread->initGeometry(offsetX,offsetY,width,height);
}

void Widget::getScreenSize()
{
    m_screenWidth = qApp->primaryScreen()->size().width();
    m_screenHeight = qApp->primaryScreen()->size().height();
}

void Widget::onStopBtnClicked()
{
    m_screenCapThread->setStop(true);
}

