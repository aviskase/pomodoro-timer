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
