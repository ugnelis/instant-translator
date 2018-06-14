#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::SettingsDialog) {
    ui->setupUi(this);

    APISettings *googleAPISettings = new APISettings(this, "google", "Google Translate API");
    googleAPISettings->readSettings();
    apiSettingsList.append(googleAPISettings);

    APISettings *tempAPISettings = new APISettings(this, "temp", "Temp");
    tempAPISettings->readSettings();
    apiSettingsList.append(tempAPISettings);

    for (int i = 0; i < apiSettingsList.count(); ++i) {
        QListWidgetItem *listWidgetItem = new QListWidgetItem(apiSettingsList.at(i)->getFullName());
        apiSettingsListWidgetItemList.append(listWidgetItem);
        ui->apisListWidget->addItem(listWidgetItem);
    }
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::on_apisListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
    int currentIndex = apiSettingsListWidgetItemList.indexOf(current);

    if (currentIndex >= 0) {
        APISettings *apiSettings = apiSettingsList.at(currentIndex);
        ui->apiKeyLineEdit->setText(apiSettings->getApiKey());
        ui->defaultSourceLanguageLineEdit->setText(apiSettings->getDefaultSourceLanguage());
        ui->defaultTargetLanguageLineEdit->setText(apiSettings->getDefaultTargetLanguage());
    }
}

void SettingsDialog::on_settingsButtonBox_accepted() {
    save();
}

void SettingsDialog::on_apiKeyLineEdit_textChanged() {
    int currentIndex = apiSettingsListWidgetItemList.indexOf(ui->apisListWidget->currentItem());

    if (currentIndex >= 0) {
        APISettings *apiSettings = apiSettingsList.at(currentIndex);
        apiSettings->setApiKey(ui->apiKeyLineEdit->text());
    }
}

void SettingsDialog::on_defaultSourceLanguageLineEdit_textChanged() {
    int currentIndex = apiSettingsListWidgetItemList.indexOf(ui->apisListWidget->currentItem());

    if (currentIndex >= 0) {
        APISettings *apiSettings = apiSettingsList.at(currentIndex);
        apiSettings->setDefaultSourceLanguage(ui->defaultSourceLanguageLineEdit->text());
    }
}

void SettingsDialog::on_defaultTargetLanguageLineEdit_textChanged() {
    int currentIndex = apiSettingsListWidgetItemList.indexOf(ui->apisListWidget->currentItem());

    if (currentIndex >= 0) {
        APISettings *apiSettings = apiSettingsList.at(currentIndex);
        apiSettings->setDefaultTargetLanguage(ui->defaultTargetLanguageLineEdit->text());
    }
}

void SettingsDialog::save() {
    for (int i = 0; i < apiSettingsList.count(); ++i) {
        APISettings *apiSettings = apiSettingsList.at(i);
        apiSettings->writeSettings();
    }
}
