#include "TimerStaysOnTopHint.h"

TimerStaysOnTopHint::TimerStaysOnTopHint(QWidget*parent) : QWidget(parent){
	ui.setupUi(this);

	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
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

void TimerStaysOnTopHint::setParentAlt(QWidget* parentAlt){
	this->parentAlt = parentAlt;
}

void TimerStaysOnTopHint::timer_tick(){
	if (parentAlt->isVisible()) {
		ui.labelTimer->setText(currentTime->toString());
	} else {
		close();
	}
	
}
