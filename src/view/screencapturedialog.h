#ifndef SCREENCAPTUREDIALOG_H
#define SCREENCAPTUREDIALOG_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QScopedPointer>
class ScreenCaptureDialogPrivate;
class ScreenCaptureDialog : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ScreenCaptureDialog);
public:
    explicit ScreenCaptureDialog(QWidget *parent = nullptr);
    ~ScreenCaptureDialog() = default;
protected:
    void paintEvent(QPaintEvent *event);
private:
    QLabel *m_timeLabel;
    QLabel *m_stopAndstartLabel;
    QPushButton *m_startButton;
    QPushButton *m_pauseButton;
    QPushButton *m_closeButton;

    QScopedPointer<ScreenCaptureDialogPrivate> d_ptr;
};

#endif // SCREENCAPTUREDIALOG_H
