#ifndef INSTANT_TRANSLATOR_SETTINGSDIALOG_H
#define INSTANT_TRANSLATOR_SETTINGSDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "utils/apisettings.h"

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
     * On apiKeyLineEdit is text changed.
     */
    void on_apiKeyLineEdit_textChanged();

    /**
     * On apiKeyLineEdit is text changed.
     */
    void on_defaultSourceLanguageLineEdit_textChanged();

    /**
     * On apiKeyLineEdit is text changed.
     */
    void on_defaultTargetLanguageLineEdit_textChanged();

private:
    /**
     * Save settings data.
     */
    void save();

    Ui::SettingsDialog *ui;
    QList<APISettings *> apiSettingsList;
    QList<QListWidgetItem *> apiSettingsListWidgetItemList;
};

#endif // INSTANT_TRANSLATOR_SETTINGSDIALOG_H
