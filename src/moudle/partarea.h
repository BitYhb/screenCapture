#ifndef PARTAREA_H
#define PARTAREA_H

#include <QObject>
#include <QWidget>
class PartArea : public QWidget
{
    Q_OBJECT
public:
    enum class BackgroundType{Gray = 0x01,Transparent};
    explicit PartArea(QWidget *parent = nullptr);
    ~PartArea();
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
signals:
    void sigDrawRelease(const QRect rect);
private:
    void drawRect(QPainter &p);
    void setGrayBackground(PartArea::BackgroundType type);
private:
    QPoint m_startPoint;
    QPoint m_endPoint;
    QRect m_drawRect;

};

#endif // PARTAREA_H
