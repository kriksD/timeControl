#pragma once

#include <QWidget>
#include <QTimer>
#include <QDialog>
#include "timeControl.h"
#include "ui_TimerStaysOnTopHint.h"

class TimerStaysOnTopHint : public QDialog
{
	Q_OBJECT

public:
	TimerStaysOnTopHint(QWidget *parent = Q_NULLPTR);
	~TimerStaysOnTopHint();

	void setCurrentTime(QTime *currentTime);

private:
	Ui::TimerStaysOnTopHint ui;

	QWidget* parent;
	QTime* currentTime;
	QTimer timer;

private slots:
	void timer_tick();
};
