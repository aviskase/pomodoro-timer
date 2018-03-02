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

#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include <QTimer>
#include <time.h>

class Runner : public QObject
{
    Q_OBJECT
public:
    explicit Runner(QObject *parent = 0);
    ~Runner();

    enum TimerType { TASK, SHORT_BREAK, LONG_BREAK };

    time_t getTimeLeft();
    bool isActive();

    void startTask();
    void startShortBreak();
    void startLongBreak();
    void pause();
    void resume();

signals:
    void tick();
    void timeout(QString timer_type);
    void recommendTask();
    void recommendShortBreak();
    void recommendLongBreak();

private slots:
    void timerTicked();

private:
    time_t time_left;
    QTimer* timer;
    TimerType timer_type;
    int tasksCount;
    int shortBreaksCount;
    int longBreaksCount;
    int cyclesCount;
};

#endif // RUNNER_H
