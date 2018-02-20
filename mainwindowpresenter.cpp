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

#include "mainwindowpresenter.h"
#include "optionsdialog.h"
#include <QShortcut>

MainWindowPresenter::MainWindowPresenter(QObject *parent, Pomodoro* pomodoro) :
    QObject(parent),
    optionsDialog(Q_NULLPTR)
{
    this->pomodoro = pomodoro;
    connect(this->pomodoro, SIGNAL(tick()), this, SLOT(updateTime()));
    connect(this->pomodoro, SIGNAL(timeout(QString)), this, SLOT(timeOut(QString)));
    connect(this->pomodoro, &Pomodoro::recommendTask, this, &MainWindowPresenter::recommendTask);
    connect(this->pomodoro, &Pomodoro::recommendShortBreak, this, &MainWindowPresenter::recommendShortBreak);
    connect(this->pomodoro, &Pomodoro::recommendLongBreak, this, &MainWindowPresenter::recommendLongBreak);
}

void MainWindowPresenter::initWindow(MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
}

void MainWindowPresenter::updateTime()
{
    int time_left = pomodoro->getTimeLeft();
    mainWindow->updateTime(time_left);
    systemTray->updateTime(time_left);
}

void MainWindowPresenter::timeOut(QString timer_type)
{
    mainWindow->showTimeOutMessage();
    systemTray->showTimeOutMessage(timer_type);
}

void MainWindowPresenter::recommendTask()
{   mainWindow->setRecommendedTask();
    systemTray->setRecommendedTask();
}

void MainWindowPresenter::recommendShortBreak()
{
    mainWindow->setRecommendedShortBreak();
    systemTray->setRecommendedShortBreak();
}

void MainWindowPresenter::recommendLongBreak()
{
    mainWindow->setRecommendedLongBreak();
    systemTray->setRecommendedLongBreak();
}

void MainWindowPresenter::handleTrayIconActivation(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (mainWindow->isHidden()) {
            mainWindow->show();
        } else {
            mainWindow->hide();
        }
    }
}

void MainWindowPresenter::init(SystemTray* systemTray)
{
    this->systemTray = systemTray;
}

void MainWindowPresenter::startShortBreak()
{
    systemTray->setResumeState();
    systemTray->setStartShortBreakIcon();
    systemTray->unsetRecommended();
    mainWindow->setResumeState();
    mainWindow->unsetRecommended();
    pomodoro->startShortBreak();
}

void MainWindowPresenter::startLongBreak()
{
    systemTray->setResumeState();
    systemTray->setStartLongBreakIcon();
    systemTray->unsetRecommended();
    mainWindow->setResumeState();
    mainWindow->unsetRecommended();
    pomodoro->startLongBreak();
}

void MainWindowPresenter::startPomodoro()
{
    systemTray->setResumeState();
    systemTray->setStartPomodoroIcon();
    systemTray->unsetRecommended();
    mainWindow->setResumeState();
    mainWindow->unsetRecommended();
    pomodoro->startPomodoro();
}

void MainWindowPresenter::pause()
{
    if (pomodoro->isActive()) {
        pomodoro->pause();
        systemTray->setPauseState();
        mainWindow->setPauseState();
    } else {
        resume();
    }
}

void MainWindowPresenter::resume()
{
    pomodoro->resume();
    systemTray->setResumeState();
    mainWindow->setResumeState();
}

void MainWindowPresenter::options()
{
    if (!optionsDialog) {
        optionsDialog = new OptionsDialog(mainWindow);
    }
    optionsDialog->show();
    optionsDialog->raise();
    optionsDialog->activateWindow();
}

void MainWindowPresenter::quit()
{
    exit(0);
}
