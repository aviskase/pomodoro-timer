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

#include "mainwindow.h"
#include <QVBoxLayout>
#include <QShortcut>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent, MainWindowPresenter* apresenter) :
    QMainWindow(parent),
    presenter(apresenter)
{
    presenter->initWindow(this);

    setFixedSize(400, 250);
    timeLine = new QTimeLabel();
    timeLine->setEmpty();
    timeLine->setAlignment(Qt::AlignCenter);

    QWidget *central = new QWidget();
    taskBtn = new QPushButton("Start task");
    shortBreakBtn = new QPushButton("Start short break");
    longBreakBtn = new QPushButton("Start long break");
    pauseBtn = new QPushButton("Pause");
    pauseBtn->setDisabled(true);
    resumeBtn = new QPushButton("Resume");
    resumeBtn->setDisabled(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(timeLine);
    QHBoxLayout *buttonsLayout1 = new QHBoxLayout;
    buttonsLayout1->addWidget(taskBtn);
    buttonsLayout1->addWidget(shortBreakBtn);
    buttonsLayout1->addWidget(longBreakBtn);
    mainLayout->addLayout(buttonsLayout1);
    QHBoxLayout *buttonsLayout2 = new QHBoxLayout;
    buttonsLayout2->addWidget(pauseBtn);
    buttonsLayout2->addWidget(resumeBtn);
    mainLayout->addLayout(buttonsLayout2);
    central->setLayout(mainLayout);
    setCentralWidget(central);

    setWindowTitle("Pomodoro Timer");
    setWindowIcon(QIcon(":/images/task.png"));

    new QShortcut(Qt::Key_T, this, SLOT(startPomodoro()));
    connect(this->taskBtn, SIGNAL (clicked()),this, SLOT (startPomodoro()));

    new QShortcut(Qt::Key_L, this, SLOT(startLongBreak()));
    connect(this->longBreakBtn, SIGNAL (clicked()),this, SLOT (startLongBreak()));

    new QShortcut(Qt::Key_S, this, SLOT(startShortBreak()));
    connect(this->shortBreakBtn, SIGNAL (clicked()),this, SLOT (startShortBreak()));

    new QShortcut(Qt::Key_P, this, SLOT(pause()));
    connect(this->pauseBtn, SIGNAL (clicked()),this, SLOT (pause()));

    new QShortcut(Qt::Key_R, this, SLOT(resume()));
    connect(this->resumeBtn, SIGNAL (clicked()),this, SLOT (resume()));

    new QShortcut(Qt::Key_O, this, SLOT(options()));
    new QShortcut(Qt::Key_Q, this, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete presenter;
}

void MainWindow::updateTime(time_t time)
{
    timeLine->setTime(time);
}

void MainWindow::showTimeOutMessage()
{
    pauseBtn->setDisabled(true);
    timeLine->setEmpty();
    show();
}

void MainWindow::setPauseState() {
    pauseBtn->setDisabled(true);
    resumeBtn->setDisabled(false);
}

void MainWindow::setResumeState() {
    pauseBtn->setDisabled(false);
    resumeBtn->setDisabled(true);
}

void MainWindow::startPomodoro() {
    presenter->startPomodoro();
}

void MainWindow::startShortBreak() {
    presenter->startShortBreak();
}

void MainWindow::startLongBreak() {
    presenter->startLongBreak();
}

void MainWindow::pause() {
    presenter->pause();
}

void MainWindow::resume() {
    presenter->resume();
}

void MainWindow::options() {
    presenter->options();
}

void MainWindow::quit() {
    presenter->quit();
}
