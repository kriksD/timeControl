#include "timeControl.h"

timeControl::timeControl(QWidget *parent) : QMainWindow(parent){
    ui.setupUi(this);

    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    setDataOfTime();
    customizeAndStartTimer();
    createTimerOnTop();

    connect(ui.buttonAdd5Minutes, SIGNAL(clicked()), this, SLOT(buttonAdd5Minutes_click()));
    connect(ui.buttonRemove5Minutes, SIGNAL(clicked()), this, SLOT(buttonRemove5Minutes_click()));
    connect(ui.buttonSetLimit, SIGNAL(clicked()), this, SLOT(buttonSetLimit_click()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timer_tick()));
}

timeControl::~timeControl() {
    saveFileTime();
}

QTime* timeControl::getCurrentTime(){
    return &currentTime;
}

void timeControl::setDataOfTime() {
    QString dataFromFile = getDataFromFileTime();

    if (dataFromFile != "FileNotFound") {
        QList<QString> listDatasIsFile = dataFromFile.split(",");

        if (listDatasIsFile.at(FilePosition::DATE_OF_LAST_VISIT) == QDate::currentDate().toString(Qt::DateFormat::ISODate)) {
            currentTime = QTime::fromString(listDatasIsFile.at(FilePosition::CURRENT_TIME), "h:mm:ss");
        }
        else {
            currentTime = QTime::fromString(listDatasIsFile.at(FilePosition::LIMIT_TIME), "h:mm:ss");
        }

        timeLimit = QTime::fromString(listDatasIsFile.at(FilePosition::LIMIT_TIME), "h:mm:ss");
    }
    else {
        setDefaultDataOfTime();
    }

    ui.timeEditLimit->setTime(timeLimit);
    ui.labelTimerView->setText(currentTime.toString());
}

QString timeControl::getDataFromFileTime() {
    QFile fileTime("timeProperties.txt");
    if (fileTime.open(QIODevice::OpenModeFlag::ReadOnly)) {
        QString dataFromFile = fileTime.readAll();
        return dataFromFile;
    } else {
        return "FileNotFound";
    }
}

void timeControl::setDefaultDataOfTime() {
    timeLimit = QTime::fromString("4:00:00", "h:mm:ss");
    currentTime = timeLimit;
}

void timeControl::saveFileTime() {
    QFile fileTime("timeProperties.txt");
    if (fileTime.open(QIODevice::OpenModeFlag::WriteOnly)) {

        QString toSaveOnFile = timeLimit.toString() + "," + currentTime.toString() + "," + 
            QDate::currentDate().toString(Qt::DateFormat::ISODate) + ","; // last coma for split \n off date
        fileTime.write(toSaveOnFile.toStdString().c_str());
    }
}

void timeControl::setTimeLimitAndChangeCurrent(QTime time){
    timeLimit = time;
    setCurrentTime(timeLimit);
    ui.labelTimerView->setText(currentTime.toString());
}

void timeControl::setCurrentTime(QTime time){
    currentTime = time;
}

void timeControl::buttonSetLimit_click(){
    setTimeLimitAndChangeCurrent(ui.timeEditLimit->time());
}

void timeControl::buttonAdd5Minutes_click(){
    if (isCurrentTimeHave5MinutesUp()) {
        currentTime = currentTime.addSecs(300);
        ui.labelTimerView->setText(currentTime.toString());
    }
}

void timeControl::buttonRemove5Minutes_click(){
    if (isCurrentTimeHave5MinutesDown()) {
        currentTime = currentTime.addSecs(-300);
        ui.labelTimerView->setText(currentTime.toString());
    }
}

bool timeControl::isCurrentTimeHave5MinutesDown(){

    if (currentTime.hour() >= 1 || currentTime.minute() >= 5) {
        return true;
    } else {
        return false;
    }
}

bool timeControl::isCurrentTimeHave5MinutesUp(){
    if (currentTime.secsTo(timeLimit) >= 300) {
        return true;
    } else {
        return false;
    }
}

void timeControl::timer_tick() {
    if (ui.checkBoxOnOffTimer->isChecked()) {

        if (QTime(0, 0, 0).secsTo(currentTime) > 0) {
            currentTime = currentTime.addSecs(-1);
            ui.labelTimerView->setText(currentTime.toString());
        } else {
            ui.checkBoxOnOffTimer->setChecked(false);
        }
    }
}

void timeControl::customizeAndStartTimer() {
    timer.setInterval(1000);
    timer.start();
}

void timeControl::createTimerOnTop() {
    TimerStaysOnTopHint* timerOnTop = new TimerStaysOnTopHint(this);
    timerOnTop->setCurrentTime(&currentTime);
    widTimerOnTop = timerOnTop;
    timerOnTop->show();
}