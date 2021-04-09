#include "TimerStaysOnTopHint.h"

TimerStaysOnTopHint::TimerStaysOnTopHint(QWidget*parent) : QDialog(parent){
	ui.setupUi(this);
	this->parent = parent;

	this->setWindowFlag(Qt::FramelessWindowHint);
	this->setWindowOpacity(0.5);
	this->setGeometry(-3, 0, this->geometry().width(), this->geometry().height());

	timer.setInterval(1000);
	timer.start();

	connect(&timer, SIGNAL(timeout()), this, SLOT(timer_tick()));
}

TimerStaysOnTopHint::~TimerStaysOnTopHint(){

}

void TimerStaysOnTopHint::setCurrentTime(QTime *currentTime){
	this->currentTime = currentTime;
}

void TimerStaysOnTopHint::timer_tick(){
	ui.labelTimer->setText(currentTime->toString());
}
