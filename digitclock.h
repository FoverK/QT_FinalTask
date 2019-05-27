#ifndef DIGITCLOCK_H
#define DIGITCLOCK_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QFont>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QPainter>
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMenuBar>
#include <QDebug>
#include <QMessageBox>
#include <QUrl>
#include <QMovie>
#include <QWizard>
const double PI = 3.14;

namespace Ui {
class DigitClock;
}

class DigitClock : public QWidget
{
    Q_OBJECT


public slots:
    void showTime();
    void on_addTime_clicked();
    void SelectClock();
    void sureClock();
    void clockPlay();
    void reveal();
    void on_ClearTime_clicked();

    void on_clearLog_clicked();

    void on_stopBtn_clicked();

public:

    QPointF rotateAngle(int angle, int length);
    void paintEvent(QPaintEvent *event);
    explicit DigitClock(QWidget *parent = 0);
    ~DigitClock();

private:
    Ui::DigitClock *ui;
    QDialog *dialog;
    QGridLayout *glayout;
    QPushButton *selectBtn;
    QPushButton *sureBtn;
    QPushButton *cancelBtn;
    QLabel *clockTime;
    QLabel *pauseTime;
    QLabel *timeLabel;
    QLabel *Label;
    QSpinBox *hBox;
    QSpinBox *mBox;
    QSpinBox *sBox;
    QFont font;
    QString clockPath;
    QMediaPlayer *player;
    QMediaPlaylist *list;
    QString clockhour,clockminute,clocksecond;
    QMovie *movie;
    QMenuBar *bar;
    QWizardPage *inforpage();
};

#endif // DIGITCLOCK_H
