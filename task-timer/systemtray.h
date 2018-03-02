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

#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QAction>
#include "mainwindowpresenter.h"
//#include "mainwindow.h"
class MainWindowPresenter;


class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTray(QObject *parent = 0, MainWindowPresenter* presenter = 0);

    void createActions();
    void createTrayIcon();
    void setStartTaskIcon();
    void setStartShortBreakIcon();
    void setStartLongBreakIcon();
    void showTimeOutMessage(QString timer_type);
    void setPauseState();
    void setResumeState();
    void updateTime(time_t);
    void setRecommendedTask();
    void setRecommendedShortBreak();
    void setRecommendedLongBreak();
    void unsetRecommended();

signals:

public slots:

private:
    MainWindowPresenter* presenter;
    QAction* startTaskAction;
    QAction* startShortBreakAction;
    QAction* startLongBreakAction;
    QAction* pauseAction;
    QAction* resumeAction;
    QAction* optionsAction;
    QAction* quitAction;
    QIcon lastIcon;
};

#endif // SYSTEMTRAY_H
