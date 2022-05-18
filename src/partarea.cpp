#include "partarea.h"
#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>
#include <cmath>
PartArea::PartArea(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    resize(parent->width(),parent->height());
    setWindowOpacity(0.5);
    setGrayBackground(BackgroundType::Gray);
}

PartArea::~PartArea()
{

}

void PartArea::mouseReleaseEvent(QMouseEvent *event)
{
    setGrayBackground(BackgroundType::Transparent);
    this->lower();
    QPoint pos = mapToGlobal(QPoint(m_drawRect.x(),m_drawRect.y()));
    QRect tmpRect(pos.x(),pos.y(),m_drawRect.width(),m_drawRect.height());
    //录制的宽度和高度要求是2的倍数
    if((tmpRect.width() % 2) != 0)
    {
        tmpRect.setWidth(tmpRect.width() + 1);
    }else if((tmpRect.height()) % 2 != 0)
    {
        tmpRect.setHeight(tmpRect.height() + 1);
    }
    emit sigDrawRelease(tmpRect);
}

void PartArea::mouseMoveEvent(QMouseEvent *event)
{
    QPoint tmpPoint = event->pos();
    if(tmpPoint.x() > m_startPoint.x() || tmpPoint.y() > m_startPoint.y())
    {
        m_endPoint = tmpPoint;
    }
    else
    {
        m_endPoint = m_startPoint;
        m_startPoint = tmpPoint;
    }
    update();
}

void PartArea::mousePressEvent(QMouseEvent *event)
{
    m_startPoint = event->pos();
}

void PartArea::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(0,176,174));
    p.setPen(pen);
    //设置画刷
//    p.setBrush(QColor(0,176,174));
    m_drawRect = QRect(m_startPoint,m_endPoint);
    drawRect(p);
}

void PartArea::drawRect(QPainter &p)
{
    p.drawRect(m_drawRect);
    if(m_drawRect.width() < 3 && m_drawRect.height() < 3)
        return;
    p.setBrush(QColor(0,176,174));
    p.drawRect(m_drawRect.x() - 8,m_drawRect.y() - 8,20,20);
    p.drawRect(m_drawRect.x() + m_drawRect.width() - 9,m_drawRect.y() - 9,20,20);
    p.drawRect(m_drawRect.x() - 10,m_drawRect.y() + m_drawRect.height() - 10,20,20);
    p.drawRect(m_drawRect.x() + m_drawRect.width() - 11,m_drawRect.y() + m_drawRect.height() - 11,20,20);
    p.setBrush(QColor(255,255,255));
}

void PartArea::setGrayBackground(BackgroundType type)
{
    if(type == BackgroundType::Gray)
        this->setStyleSheet("QWidget{background-color: rgba(0,0,0,150);border: 1px solid rgb(18，95，83);}");
    else
        this->setStyleSheet("QWidget{background-color: rgba(0,0,0,0);border: 1px solid rgb(18，95，83);}");
}
