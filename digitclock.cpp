#include "digitclock.h"
#include "ui_digitclock.h"

DigitClock::DigitClock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DigitClock)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    list = new QMediaPlaylist(this);
    bar = new QMenuBar(this);
    QAction *about = new QAction(this);
    about->setText("关于");

    bar->addAction(about);
    connect(about,&QAction::triggered,this,&DigitClock::reveal);
    movie = new QMovie("E:/Qt-PKG/day-two/DigitClock/image.gif");
    movie->setScaledSize(QSize(342,213));
    ui->label->setMovie(movie);
    movie->start();

    ui->comboBox->addItem("暂无闹钟");

    font.setPixelSize(20);
    font.setFamily("simsun");

    Label = new QLabel(this);
    Label->setText("闹钟与铃声");
    Label->setFont(font);
    Label->move(380,30);

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&DigitClock::showTime);
    connect(timer,&QTimer::timeout,this,&DigitClock::clockPlay);
    timer->start(1000);


    setFixedSize(730,550);
}

DigitClock::~DigitClock()
{
    delete ui;
}

void DigitClock::showTime()
{
    QTime Nowtime = QTime::currentTime();
    QString format = Nowtime.toString("hh:mm:ss");
    ui->lcdNumber->setFont(font);
    ui->lcdNumber->display(format);
}

void DigitClock::on_addTime_clicked()
{
    dialog = new QDialog(this);
    glayout = new QGridLayout;
    clockTime = new QLabel(this);
    pauseTime = new QLabel(this);
    selectBtn = new QPushButton(this);
    sureBtn = new QPushButton(this);
    cancelBtn = new QPushButton(this);
    hBox = new QSpinBox(this);
    mBox = new QSpinBox(this);
    sBox = new QSpinBox(this);

    selectBtn->setText("选择闹铃");
    sureBtn->setText("确认");
    cancelBtn->setText("取消");
    clockTime->setText("闹钟时间");
    pauseTime->setText("暂停时间:");

    hBox->setRange(0,23);
    mBox->setRange(0,59);
    sBox->setRange(0,59);

//    glayout->addWidget(clockTime,0,0);
//    glayout->addWidget(lcdNumber_H,0,1,1,1);
//    glayout->addWidget(lcdNumber_M,0,2,1,1);
//    glayout->addWidget(lcdNumber_S,0,3,1,1);
    glayout->addWidget(pauseTime,0,0);
    glayout->addWidget(hBox,0,1);
    glayout->addWidget(mBox,0,2);
    glayout->addWidget(sBox,0,3);
    glayout->addWidget(selectBtn,1,0,1,4);
    glayout->addWidget(sureBtn,2,0,1,2);
    glayout->addWidget(cancelBtn,2,2,1,2);

    //    lcdNumber_H->setDigitCount(2);
    //    lcdNumber_H->display(hBox->text());
    //    lcdNumber_M->setDigitCount(2);
    //    lcdNumber_M->display(mBox->text());
    //    lcdNumber_S->setDigitCount(2);
    //    lcdNumber_S->display(sBox->text());

    connect(selectBtn,&QPushButton::clicked,this,&DigitClock::SelectClock);
    connect(cancelBtn,&QPushButton::clicked,dialog,&QDialog::close);
    connect(sureBtn,&QPushButton::clicked,this,&DigitClock::sureClock);


    dialog->setLayout(glayout);
    dialog->setWindowTitle("闹钟添加");
    dialog->setFixedSize(400,200);
    dialog->exec();
}

void DigitClock::paintEvent(QPaintEvent *event)
{

    QTime time = QTime::currentTime();
    int Hour = time.hour();
    int Minute = time.minute();
    int Second = time.second();

//    QDateTime dateTime = QDateTime::currentDateTime();
//    timeLabel = new QLabel(this);
//    timeLabel->setText(dateTime.toString("yyyy-MM-dd hh:mm:ss ddd"));

    QPainter painter(this);
    QPen pen;

    pen.setWidth(1);
    pen.setColor("#333");
    painter.setPen(pen);
    for(int i=0; i<60; i++)
    {
        painter.drawLine(rotateAngle(6*i, 100), rotateAngle(6*i, 93));
    }
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(150, 150), 100, 100);
    pen.setWidth(3);
    painter.setPen(pen);
    for(int i=0; i<12; i++)
    {
        painter.drawLine(rotateAngle(30*i, 100), rotateAngle(30*i, 80));
    }

    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(6*Second, 80));
    pen.setWidth(6);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(6*Minute, 60));
    pen.setWidth(8);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(0.5*(Hour*60+Minute), 40));

    update();
}

QPointF DigitClock::rotateAngle(int angle, int length)
{
    int x, y;

    x = 150+length*sin(angle*PI/180);
    y = 150-length*cos(angle*PI/180);

    return QPointF(x, y);
}

void DigitClock::SelectClock()
{
    clockPath = QFileDialog::getOpenFileName(this,"选择闹钟铃声",":/clock","(* mp3)");
}

void DigitClock::sureClock()
{
    ui->comboBox->clear();
    clockhour = hBox->text();
    clockminute = mBox->text();
    clocksecond = sBox->text();
    QLabel *clock[5] = {
        ui->hourLabel,ui->pointLable_1,ui->minuteLable,
        ui->pointLabel_2,ui->secondLabel
    };
    QFont font;
    font.setFamily("Times");
    font.setPointSize(20);
    for(int i = 0;i<5;i++)
    {
        clock[i]->setFont(font);
    }

//    if(clockhour.toInt()<10)
//    {
//         clock[0]->setText("0"+clockhour);
//    }
//    else
//    {
//        clock[0]->setText(clockhour);
//    }
//    clock[1]->setText(":");

//    if(clockminute.toInt()<10)
//    {
//         clock[2]->setText("0"+clockminute);
//    }
//    else
//    {
//        clock[2]->setText(clockminute);
//    }
//    clock[3]->setText(":");

//    if(clocksecond.toInt()<10)
//    {
//         clock[4]->setText("0"+clocksecond);
//    }
//    else
//    {
//        clock[4]->setText(clocksecond);
//    }
    clock[0]->setText(clockhour);
    clock[1]->setText(":");
    clock[2]->setText(clockminute);
    clock[3]->setText(":");
    clock[4]->setText(clocksecond);
    ui->musicPath->setText(clockPath);

    ui->comboBox->addItem(clockhour+":"+clockminute+":"+clocksecond+"    "+ clockPath);


    dialog->close();
}

void DigitClock::clockPlay()
{

    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();
    int timeS = time.second();


        if(timeH == ui->hourLabel->text().toInt()
           && timeM == ui->minuteLable->text().toInt()
           && timeS == ui->secondLabel->text().toInt())
        {

            list->addMedia(QUrl::fromLocalFile(ui->musicPath->text()));
            list->setCurrentIndex(1);
            player->setPlaylist(list);
            player->play();

        }

    update();
}

void DigitClock::on_ClearTime_clicked()
{
    ui->hourLabel->clear();
    ui->minuteLable->clear();
    ui->pointLabel_2->clear();
    ui->pointLable_1->clear();
    ui->secondLabel->clear();
    ui->musicPath->clear();
}

void DigitClock::on_clearLog_clicked()
{
    ui->comboBox->clear();
}



void DigitClock::on_stopBtn_clicked()
{
    player->stop();
}

void DigitClock::reveal()
{
    QWizard wizard(this);
    wizard.setWindowTitle("程序信息");
    wizard.addPage(inforpage());
    wizard.exec();

}
QWizardPage *DigitClock::inforpage()
{
    QWizardPage *page = new QWizardPage();
    page->setTitle("程序名称：缩减版闹钟\n姓名：王浩\n班级：软件工程174班\n学号：8002117168\n版本信息：CLOCK1.0\n完成时间：2018年9月22日");
    return page;
}
