############################################################################
##
## Copyright (C) 2018 Yuliya Bagriy.
##
## Copyright (C) 2012 Dmitriy Sukharev.
## All rights reserved.
## Contact: Dmitriy Sukharev (ecuna@mail.ru)
##
## This file is part of Task Timer.
##
## Task Timer is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published
## by the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## Task Timer is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with Task Timer.  If not, see <http://www.gnu.org/licenses/>.
##
############################################################################

#-------------------------------------------------
#
# Project created by QtCreator 2012-06-24T09:56:22
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = task-timer
TEMPLATE = app


SOURCES += main.cpp\
        qtimelabel.cpp \
        mainwindow.cpp \
    runner.cpp \
    systemtray.cpp \
    mainwindowpresenter.cpp \
    optionsdialog.cpp

HEADERS  += mainwindow.h \
    qtimelabel.h \
    runner.h \
    systemtray.h \
    mainwindowpresenter.h \
    optionsdialog.h

OTHER_FILES += \
    icon.rc

RESOURCES += \
    systray.qrc

RC_FILE += icon.rc

ICON = images/task.png
