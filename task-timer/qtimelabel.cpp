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

#include "qtimelabel.h"

QTimeLabel::QTimeLabel(QWidget *parent) :
    QLabel(parent)
{
    font = new QFont("Courier New");
}

QTimeLabel::~QTimeLabel()
{
    delete(font);
}

QString formatTime1(int seconds)
{
    return QString("%1:%2").arg(seconds / 60, 2, 10, QChar('0')).arg(seconds % 60, 2, 10, QChar('0'));
}

void QTimeLabel::setTime(int time)
{
    font->setPixelSize(72);
    setFont(*font);
    QLabel::setText(formatTime1(time));
}

void QTimeLabel::setEmpty()
{
    font->setPixelSize(72);
    setFont(*font);
    QLabel::setText("--:--");
}
