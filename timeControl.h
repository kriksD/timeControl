#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QFile>
#include <QDebug>
//#include <QMediaPlayer>
#include "ui_timeControl.h"
#include "TimerStaysOnTopHint.h"

class timeControl : public QMainWindow{
    Q_OBJECT

public:
    timeControl(QWidget *parent = Q_NULLPTR);
    ~timeControl();
    QTime* getCurrentTime();

private:
    Ui::timeControlClass ui;
    QTimer timer;
    QTime currentTime;
    QTime timeLimit;
    QDate lastDate = QDate::currentDate();
    QWidget* widTimerOnTop;
    enum FilePosition {
        LIMIT_TIME,
        CURRENT_TIME,
        DATE_OF_LAST_VISIT
    };

    QString getDataFromFileTime();
    void saveFileTime();
    void setDataOfTime();
    void setDefaultDataOfTime();
    void setTimeLimitAndChangeCurrent(QTime time);
    void setCurrentTime(QTime time);
    bool isCurrentTimeHave5MinutesUp();
    bool isCurrentTimeHave5MinutesDown();
    void customizeAndStartTimer();
    void createTimerOnTop();

private slots:
    void buttonSetLimit_click();
    void buttonAdd5Minutes_click();
    void buttonRemove5Minutes_click();
    void timer_tick();
};
