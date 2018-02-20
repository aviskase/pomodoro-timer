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

#include "systemtray.h"
#include <QMenu>

SystemTray::SystemTray(QObject *parent, MainWindowPresenter *presenter) :
    QSystemTrayIcon(parent),
    presenter(presenter)
{
    QIcon icon = QIcon(":/images/task.png");
    setIcon(icon);

    presenter->init(this);
    createActions();
    createTrayIcon();

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            presenter, SLOT(handleTrayIconActivation(QSystemTrayIcon::ActivationReason)));
}

void SystemTray::createActions()
 {
    startPomodoroAction = new QAction(QIcon(":/images/task_pr.png"), tr("Start &task"), this);
    startShortBreakAction = new QAction(QIcon(":/images/short_break.png"), tr("Start short &break"), this);
    startLongBreakAction = new QAction(QIcon(":/images/long_break.png"), tr("Start &long break"), this);
    pauseAction = new QAction(QIcon(":/images/pause.png"), tr("Pause"), this);
    resumeAction = new QAction(QIcon(":/images/pause.png"), tr("Resume"), this);
    optionsAction = new QAction(tr("&Options"), this);
    quitAction = new QAction(tr("&Quit"), this);
    connect(startPomodoroAction, SIGNAL(triggered()), presenter, SLOT(startPomodoro()));
    connect(startShortBreakAction, SIGNAL(triggered()), presenter, SLOT(startShortBreak()));
    connect(startLongBreakAction, SIGNAL(triggered()), presenter, SLOT(startLongBreak()));
    connect(pauseAction, SIGNAL(triggered()), presenter, SLOT(pause()));
    connect(resumeAction, SIGNAL(triggered()), presenter, SLOT(resume()));
    connect(optionsAction, SIGNAL(triggered()), presenter, SLOT(options()));
    connect(quitAction, SIGNAL(triggered()), presenter, SLOT(quit()));
 }

void SystemTray::createTrayIcon()
{
    QMenu* trayIconMenu = new QMenu();
    trayIconMenu->addAction(startPomodoroAction);
    trayIconMenu->addAction(startShortBreakAction);
    trayIconMenu->addAction(startLongBreakAction);
    trayIconMenu->addAction(pauseAction);
    trayIconMenu->addAction(resumeAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(optionsAction);
    trayIconMenu->addAction(quitAction);

    setContextMenu(trayIconMenu);
    pauseAction->setVisible(false);
    resumeAction->setVisible(false);
}

void SystemTray::setStartShortBreakIcon()
{
    setIcon(QIcon(":/images/short_break.png"));
}

void SystemTray::setStartLongBreakIcon()
{
    setIcon(QIcon(":/images/long_break.png"));
}

void SystemTray::setStartPomodoroIcon()
{
    setIcon(QIcon(":/images/task.png"));
}

void SystemTray::showTimeOutMessage(QString timer_type)
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
    setIcon(QIcon(":/images/alarm.png"));
    showMessage("Time out", timer_type + " is over!", icon, 60 * 1000);
    setToolTip("pomodoro-timer");
    pauseAction->setVisible(false);
}

void SystemTray::setPauseState()
{
    lastIcon = icon();
    pauseAction->setVisible(false);
    resumeAction->setVisible(true);
    setIcon(QIcon(":/images/pause.png"));
}

void SystemTray::setResumeState()
{
    pauseAction->setVisible(true);
    resumeAction->setVisible(false);
    setIcon(lastIcon);
}

void SystemTray::updateTime(time_t time)
{
    QString time_s = QString("%1:%2").arg(time / 60, 2, 10, QChar('0')).arg(time % 60, 2, 10, QChar('0'));
    setToolTip(time_s);
}

void SystemTray::setRecommendedTask()
{
    startPomodoroAction->setIcon(QIcon(":/images/task_pr.png"));
}

void SystemTray::setRecommendedShortBreak()
{
    startShortBreakAction->setIcon(QIcon(":/images/short_break_pr.png"));
}

void SystemTray::setRecommendedLongBreak()
{
    startLongBreakAction->setIcon(QIcon(":/images/long_break_pr.png"));
}

void SystemTray::unsetRecommended()
{
    startPomodoroAction->setIcon(QIcon(":/images/task.png"));
    startShortBreakAction->setIcon(QIcon(":/images/short_break.png"));
    startLongBreakAction->setIcon(QIcon(":/images/long_break.png"));
}



