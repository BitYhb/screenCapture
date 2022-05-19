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
    ~ScreenCaptureDialog();
private slots:
    void onStartButtonClicked();
    void onPauseButtonClicked();
    void onCloseButtonClicked();
    void onTimeout();
protected:
    void paintEvent(QPaintEvent *event);
private:
    QScopedPointer<ScreenCaptureDialogPrivate> d_ptr;
};

#endif // SCREENCAPTUREDIALOG_H
