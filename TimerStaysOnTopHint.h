#pragma once

#include <QWidget>
#include <QTimer>
#include <QDialog>
#include "timeControl.h"
#include "ui_TimerStaysOnTopHint.h"

class TimerStaysOnTopHint : public QWidget
{
	Q_OBJECT

public:
	TimerStaysOnTopHint(QWidget *parent = Q_NULLPTR);
	~TimerStaysOnTopHint();

	void setCurrentTime(QTime *currentTime);
	void setParentAlt(QWidget *parentAlt);

private:
	Ui::TimerStaysOnTopHint ui;

	QWidget* parentAlt;
	QTime* currentTime;
	QTimer timer;

private slots:
	void timer_tick();
};
