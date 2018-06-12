#ifndef INSTANT_TRANSLATOR_SETTINGSDIALOG_H
#define INSTANT_TRANSLATOR_SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class SettingsDialog;
}

/**
 * Settings dialog class.
 */
class SettingsDialog : public QDialog {
Q_OBJECT

public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     */
    explicit SettingsDialog(QWidget *parent = nullptr);

    /**
     * Destructor.
     */
    ~SettingsDialog();

private:
    Ui::SettingsDialog *ui;
};

#endif // INSTANT_TRANSLATOR_SETTINGSDIALOG_H
