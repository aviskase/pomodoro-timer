/****************************************************************************
 **
 ** Copyright (C) 2018 Yuliya Bagriy.
 **
 ** Copyright (C) 2012 Dmitriy Sukharev.
 ** All rights reserved.
 ** Contact: Dmitriy Sukharev (ecuna@mail.ru)
 **
 ** This file is part of Task Timer.
 **
 ** Task Timer is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published
 ** by the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** Task Timer is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with Task Timer.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/

#include "runner.h"

#include <QSettings>

Runner::Runner(QObject *parent) :
    QObject(parent)
{
    time_left = 0;
    tasksCount = 0;
    shortBreaksCount = 0;
    longBreaksCount = 0;
    cyclesCount = 0;
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTicked()));
}

Runner::~Runner()
{
    delete timer;
}

void Runner::startTask()
{
    timer->stop();
    QSettings s;
    time_left = 60 * s.value("task_time", 25).toInt();
    timer_type = TimerType::TASK;
    timer->start();
}

void Runner::startShortBreak()
{
    timer->stop();
    QSettings s;
    time_left = 60 * s.value("short_break_time", 5).toInt();
    timer_type = TimerType::SHORT_BREAK;
    timer->start();
}

void Runner::startLongBreak()
{
    timer->stop();
    QSettings s;
    time_left = 60 * s.value("long_break_time", 15).toInt();
    timer_type = TimerType::LONG_BREAK;
    timer->start();
}

void Runner::pause()
{
    timer->stop();
}

void Runner::resume()
{
    timer->start();
}

void Runner::timerTicked()
{
    time_left--;
    emit tick();
    if (time_left <= 0) {
        time_left = 0;
        timer->stop();

        switch(timer_type) {
        case TASK:
            tasksCount++;
            // TODO: Naive check for now. Should think about proper handling of consecutive break, pauses (?), etc.
            if (tasksCount % 4 == 0) emit recommendLongBreak();
            else emit recommendShortBreak();
            emit timeout("Task");
            break;
        case SHORT_BREAK:
            shortBreaksCount++;
            emit recommendTask();
            emit timeout("Short break");
            break;
        case LONG_BREAK:
            longBreaksCount++;
            emit recommendTask();
            emit timeout("Long break");
            break;
        }
    }
}

time_t Runner::getTimeLeft()
{
    return time_left;
}

bool Runner::isActive()
{
    return timer->isActive();
}
