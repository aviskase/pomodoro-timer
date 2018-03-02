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

#include "optionsdialog.h"

#include <QFormLayout>
#include <QPushButton>
#include <QSettings>

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent)
{
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    QPushButton* applyButton = buttonBox->button(QDialogButtonBox::Apply);
    connect(applyButton, &QPushButton::clicked, this, &OptionsDialog::apply);

    QSettings s;
    taskSpinBox = new QSpinBox();
    taskSpinBox->setValue(s.value("task_time", 25).toInt());
    shortBreakSpinBox = new QSpinBox();
    shortBreakSpinBox->setValue(s.value("short_break_time", 5).toInt());
    longBreakSpinBox = new QSpinBox();
    longBreakSpinBox->setValue(s.value("long_break_time", 15).toInt());

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&Task:"), taskSpinBox);
    formLayout->addRow(tr("&Short break:"), shortBreakSpinBox);
    formLayout->addRow(tr("&Long break:"), longBreakSpinBox);
    formLayout->addRow(buttonBox);
    setLayout(formLayout);
    layout()->setSizeConstraint( QLayout::SetFixedSize ) ;
    setSizeGripEnabled(false) ;
    setWindowTitle("Options");
}

OptionsDialog::~OptionsDialog()
{
}

void OptionsDialog::accept()
{
    saveSettings();
    close();
}

void OptionsDialog::apply()
{
    saveSettings();
}

void OptionsDialog::saveSettings()
{
    QSettings s;
    s.setValue("task_time", taskSpinBox->value());
    s.setValue("short_break_time", shortBreakSpinBox->value());
    s.setValue("long_break_time", longBreakSpinBox->value());
}
