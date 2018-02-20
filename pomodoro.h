/****************************************************************************
 **
 ** Copyright (C) 2012 Dmitriy Sukharev.
 ** All rights reserved.
 ** Contact: Dmitriy Sukharev (ecuna@mail.ru)
 **
 ** This file is part of Pomodoro Timer.
 **
 ** Pomodoro Timer is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published
 ** by the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** Pomodoro Timer is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with Pomodoro Timer.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/

#ifndef POMODORO_H
#define POMODORO_H

#include <QObject>
#include <QTimer>
#include <time.h>

class Pomodoro : public QObject
{
    Q_OBJECT
public:
    explicit Pomodoro(QObject *parent = 0);
    ~Pomodoro();

    enum TimerType { TASK, SHORT_BREAK, LONG_BREAK };

    time_t getTimeLeft();
    bool isActive();

    void startPomodoro();
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

#endif // POMODORO_H
