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
