/****************************************************************************
 **
 ** Copyright (C) 2018 Yuliya Bagriy.
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

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QSpinBox>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();

private slots:
    void accept();
    void apply();
private:
    QDialogButtonBox* buttonBox;
    QSpinBox* taskSpinBox;
    QSpinBox* shortBreakSpinBox;
    QSpinBox* longBreakSpinBox;
    void saveSettings();
};

#endif // OPTIONSDIALOG_H
