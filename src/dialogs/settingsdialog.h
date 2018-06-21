#ifndef INSTANT_TRANSLATOR_SETTINGSDIALOG_H
#define INSTANT_TRANSLATOR_SETTINGSDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QAbstractButton>
#include <QSettings>
#include "utils/apisettings.h"
#include "utils/appsettings.h"

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
     * @param appSettings App settings.
     */
    SettingsDialog(QWidget *parent, AppSettings *appSettings);

    /**
     * Destructor.
     */
    ~SettingsDialog();

    /**
     * Set App settings.
     * @param appSettings App settings.
     */
    void setAppSettings(AppSettings *appSettings);

private slots:

    /**
     * On apisListWidget is current item changed.
     * @param current Current list item.
     * @param previous Previous list item.
     */
    void on_apisListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    /**
     * On settingsButtonBox is accepted.
     */
    void on_settingsButtonBox_accepted();

    /**
     * On settingsButtonBox is clicked;
     * @param button Button.
     */
    void on_settingsButtonBox_clicked(QAbstractButton *button);

private:
    /**
     * Save settings data.
     */
    void saveSettings();

    /**
     * Load appSettings.
     */
    void loadSettings();

    Ui::SettingsDialog *ui;
    AppSettings *appSettings;
    QList<QListWidgetItem *> apiSettingsListWidgetItemList;
};

#endif // INSTANT_TRANSLATOR_SETTINGSDIALOG_H
