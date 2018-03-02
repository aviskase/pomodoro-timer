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

#include "mainwindowpresenter.h"
#include "optionsdialog.h"
#include <QShortcut>

MainWindowPresenter::MainWindowPresenter(QObject *parent, Runner* runner) :
    QObject(parent),
    optionsDialog(Q_NULLPTR)
{
    this->runner = runner;
    connect(this->runner, SIGNAL(tick()), this, SLOT(updateTime()));
    connect(this->runner, SIGNAL(timeout(QString)), this, SLOT(timeOut(QString)));
    connect(this->runner, &Runner::recommendTask, this, &MainWindowPresenter::recommendTask);
    connect(this->runner, &Runner::recommendShortBreak, this, &MainWindowPresenter::recommendShortBreak);
    connect(this->runner, &Runner::recommendLongBreak, this, &MainWindowPresenter::recommendLongBreak);
}

void MainWindowPresenter::initWindow(MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
}

void MainWindowPresenter::updateTime()
{
    int time_left = runner->getTimeLeft();
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
    runner->startShortBreak();
}

void MainWindowPresenter::startLongBreak()
{
    systemTray->setResumeState();
    systemTray->setStartLongBreakIcon();
    systemTray->unsetRecommended();
    mainWindow->setResumeState();
    mainWindow->unsetRecommended();
    runner->startLongBreak();
}

void MainWindowPresenter::startTask()
{
    systemTray->setResumeState();
    systemTray->setStartTaskIcon();
    systemTray->unsetRecommended();
    mainWindow->setResumeState();
    mainWindow->unsetRecommended();
    runner->startTask();
}

void MainWindowPresenter::pause()
{
    if (runner->isActive()) {
        runner->pause();
        systemTray->setPauseState();
        mainWindow->setPauseState();
    } else {
        resume();
    }
}

void MainWindowPresenter::resume()
{
    runner->resume();
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
