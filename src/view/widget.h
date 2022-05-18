#ifndef WIDGET_H
#define WIDGET_H
#include <QRect>
#include <QWidget>
#include <QPushButton>

#include "src/core/screencapture.h"
#include "src/moudle/partarea.h"
#include "src/view/screencapturedialog.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onStopBtnClicked();
    void onStartBtnClicked();
    void onpartBtnClicked();
    void onSigDrawRelease(const QRect rect);
    void captureInit(const int offsetX,const int offsetY,const int width,const int height);
private:
    void getScreenSize();
private:
    ScreenCapture *m_screenCapThread;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QPushButton *partBtn;
    ScreenCaptureDialog *s;
    int m_screenWidth;
    int m_screenHeight;
    PartArea *partWidget;
};
#endif // WIDGET_H
