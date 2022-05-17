#include "widget.h"
#include "ui_widget.h"

#include <QThread>
#include <QScreen>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    startBtn = new QPushButton(this);
    stopBtn  = new QPushButton(this);
    partBtn  = new QPushButton(this);
    qDebug() << "main thread:" <<QThread::currentThreadId();
    startBtn->setGeometry(0,0,120,60);
    stopBtn->setGeometry(300,0,120,60);
    partBtn->setGeometry(150,0,120,60);
    startBtn->setText("start");
    stopBtn->setText("stop");
    partBtn->setText("part");

    QObject::connect(startBtn,&QPushButton::clicked,this,&Widget::onStartBtnClicked);
    QObject::connect(stopBtn,&QPushButton::clicked,this,&Widget::onStopBtnClicked);
    QObject::connect(partBtn,&QPushButton::clicked,this,&Widget::onpartBtnClicked);

    m_screenCapThread = new ScreenCapture;
}

Widget::~Widget()
{
    m_screenCapThread->wait();
    m_screenCapThread->quit();
}

void Widget::onStartBtnClicked()
{
    getScreenSize();
    partCaptureInit(0,0,m_screenWidth,m_screenHeight);
    m_screenCapThread->start();
}

void Widget::onpartBtnClicked()
{
    qDebug() << "do part";
    partCaptureInit(100,100,800,800);
    m_screenCapThread->start();
}

void Widget::partCaptureInit(const int offsetX, const int offsetY, const int width, const int height)
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

