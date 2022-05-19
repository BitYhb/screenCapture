#include "screencapturedialog.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QDebug>
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

    QTimer *m_timer;
    QTime m_time;

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

    m_timer = new QTimer(q);
    m_time.setHMS(0,0,0,0);

    QObject::connect(m_startButton,&QPushButton::clicked,q,&ScreenCaptureDialog::onStartButtonClicked);
    QObject::connect(m_pauseButton,&QPushButton::clicked,q,&ScreenCaptureDialog::onPauseButtonClicked);
    QObject::connect(m_closeButton,&QPushButton::clicked,q,&ScreenCaptureDialog::onCloseButtonClicked);
    QObject::connect(m_timer,&QTimer::timeout,q,&ScreenCaptureDialog::onTimeout);
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
                                 "  background:url(:/resources/icon/screenCapture_stop.svg) center no-repeat;"
                                 "  background-color:transparent;"
                                 "}\n"
                                 "QPushButton::checked"
                                 "{"
                                 "  background:url(:/resources/icon/screenCapture_stop_highlight.svg) center no-repeat;"
                                 "  background-color:transparent;"
                                 "}\n"
                                 "QPushButton::pressed"
                                 "{"
                                 "  background:url(:/resources/icon/screenCapture_start_highlight.svg) center no-repeat;"
                                 "  background-color:transparent;"
                                 "}\n"
                                 "QPushButton::hover"
                                 "{"
                                 "  background:url(:/resources/icon/screenCapture_stop_highlight.svg) center no-repeat;"
                                 "  background-color:transparent;"
                                 "}\n");
    m_pauseButton->setStyleSheet("QPushButton"
                                 "{"
                                 "  background:url(:/resources/icon/screenCapture_pause.svg) center no-repeat;"
                                 "  background-color:transparent;"
                                 "}"
                                 "QPushButton::hover"
                                 "{"
                                 "  background:url(:/resources/icon/screenCapture_pause_highlight.svg) center no-repeat;"
                                 "  background-color:transparent;"
                                 "}"
                                 "QPushButton::pressed"
                                 "{"
                                 "  background:url(:/resources/icon/screenCapture_pause_highlight.svg) center no-repeat;"
                                 "  background-color:transparent;"
                                 "}");
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

ScreenCaptureDialog::~ScreenCaptureDialog()
{
    Q_D(ScreenCaptureDialog);
    if(d->m_closeButton)
        delete d->m_closeButton;
    if(d->m_pauseButton)
        delete d->m_pauseButton;
    if(d->m_startButton)
        delete d->m_startButton;
    if(d->m_stopAndstartLabel)
        delete d->m_stopAndstartLabel;
    if(d->m_timeLabel)
        delete d->m_timeLabel;
    if(d->m_timer)
        delete d->m_timer;

}

void ScreenCaptureDialog::onStartButtonClicked()
{
    Q_D(ScreenCaptureDialog);
    if(d->m_timer->isActive())
        d->m_timer->stop();
    d->m_timer->start(1000);
}

void ScreenCaptureDialog::onPauseButtonClicked()
{
    Q_D(ScreenCaptureDialog);
    if(d->m_timer->isActive())
    {
        d->m_timer->stop();
        d->m_time.setHMS(0,0,0);
        d->m_timeLabel->setText(d->m_time.toString("hh:mm:ss"));
    }
}

void ScreenCaptureDialog::onCloseButtonClicked()
{
    this->close();
    delete this;
}

void ScreenCaptureDialog::onTimeout()
{
    Q_D(ScreenCaptureDialog);
    d->m_time = d->m_time.addSecs(1);
    d->m_timeLabel->setText(d->m_time.toString("hh:mm:ss"));
}

void ScreenCaptureDialog::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
