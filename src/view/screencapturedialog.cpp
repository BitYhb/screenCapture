#include "screencapturedialog.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>

class ScreenCaptureDialogPrivate
{
    Q_DECLARE_PUBLIC(ScreenCaptureDialog);
public:
    ScreenCaptureDialogPrivate(ScreenCaptureDialog*object)
        :q_ptr(object)
    {}
private:
    void init();
    void setStyle();
    void setLayout();
private:
    QLabel *m_timeLabel;
    QLabel *m_stopAndstartLabel;
    QPushButton *m_startButton;
    QPushButton *m_pauseButton;
    QPushButton *m_closeButton;

    ScreenCaptureDialog* const q_ptr;

};
void ScreenCaptureDialogPrivate::init()
{
    Q_Q(ScreenCaptureDialog);
    q->setFixedSize(289,34);
    q->setWindowFlags(Qt::FramelessWindowHint);

    q->setObjectName("ScreenCaptrueDialog");
    m_timeLabel = new QLabel(q);
    m_timeLabel->setText("00:00:00");
    m_startButton = new QPushButton(q);
    m_pauseButton = new QPushButton(q);
    m_closeButton = new QPushButton(q);
    m_stopAndstartLabel = new QLabel(q);
    m_stopAndstartLabel->setText("Stop");

    m_timeLabel->setObjectName("timeLabel");
    m_timeLabel->setMinimumSize(100,25);
    m_timeLabel->setAlignment(Qt::AlignCenter);

    m_startButton->setObjectName("startButton");
    m_startButton->setFixedSize(22,23);

    m_pauseButton->setObjectName("pauseButton");
    m_pauseButton->setFixedSize(22,23);

    m_closeButton->setObjectName("closeButton");
    m_closeButton->setFixedSize(22,23);

    m_stopAndstartLabel->setObjectName("stopAndstartLabel");
    m_stopAndstartLabel->setAlignment(Qt::AlignCenter);

}
void ScreenCaptureDialogPrivate::setStyle()
{
    Q_Q(ScreenCaptureDialog);
    q->setStyleSheet("QWidget#ScreenCaptrueDialog{background:#4E5055;border-radius:16px;}");
    m_stopAndstartLabel->setStyleSheet("QLabel#stopAndstartLabel"
                                       "{"
                                       "    font-family: PingFang SC;"
                                       "    font-weight: 400;"
                                       "    font-size: 15px;"
                                       "    line-height: 21px;"
                                       "    color: #FFFFFF;"
                                       "}");
    m_timeLabel->setStyleSheet("QLabel#timeLabel"
                               "{"
                               "    background: rgba(35, 229, 197, 0.2);"
                               "    border: 1px solid #2B4C4A;"
                               "    color: #FFFFFF;"
                               "    font-size:15px;"
                               "    font-family: PingFang SC;"
                               "    box-shadow: inset 0px 0px 4px 4px rgba(0, 0, 0, 0.1);"
                               "    border-radius: 2px;"
                               "}");
    m_startButton->setStyleSheet("QPushButton"
                                 "{"
                                 "background:url(:/resources/icon/screenCapture_stop.svg) center no-repeat;"
                                 "  background-color:transparent;}");
    m_pauseButton->setStyleSheet("QPushButton"
                                 "{"
                                 "  background:url(:/resources/icon/screenCapture_pause.svg) center no-repeat;"
                                 "  background-color:transparent;}");
    m_closeButton->setStyleSheet("QPushButton"
                                 "{"
                                 "  background:url(:/resources/icon/screenCapture_close.svg) center no-repeat;"
                                 "  background-color:transparent;}");
}

void ScreenCaptureDialogPrivate::setLayout()
{
    Q_Q(ScreenCaptureDialog);
    QHBoxLayout *hboxlayout = new QHBoxLayout(q);
    hboxlayout->setSpacing(10);
    hboxlayout->setContentsMargins(15,4,11,4);
    hboxlayout->addWidget(m_stopAndstartLabel);
    hboxlayout->addWidget(m_timeLabel);
    hboxlayout->addWidget(m_startButton);
    hboxlayout->addWidget(m_pauseButton);
    hboxlayout->addWidget(m_closeButton);
    q->QWidget::setLayout(hboxlayout);
}

ScreenCaptureDialog::ScreenCaptureDialog(QWidget *parent)
    : QWidget{parent}
    , d_ptr(new ScreenCaptureDialogPrivate(this))
{
    Q_D(ScreenCaptureDialog);
    d->init();
    d->setLayout();
    d->setStyle();
}
void ScreenCaptureDialog::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
