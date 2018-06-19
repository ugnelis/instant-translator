#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent, AppSettings *appSettings) :
        QDialog(parent),
        ui(new Ui::SettingsDialog),
        appSettings(appSettings) {
    ui->setupUi(this);

    loadSettings();
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::setAppSettings(AppSettings *appSettings) {
    this->appSettings = appSettings;
    loadSettings();
}

void SettingsDialog::on_apisListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
    int currentIndex = apiSettingsListWidgetItemList.indexOf(current);

    if (currentIndex >= 0) {
        APISettings *apiSettings = appSettings->getApiSettingsList().at(currentIndex);
        ui->apiKeyLineEdit->setText(apiSettings->getApiKey());
        ui->textTypeLineEdit->setText(apiSettings->getTextType());
        ui->defaultSourceLanguageLineEdit->setText(apiSettings->getDefaultSourceLanguage());
        ui->defaultTargetLanguageLineEdit->setText(apiSettings->getDefaultTargetLanguage());
    }
}

void SettingsDialog::on_settingsButtonBox_accepted() {
    saveSettings();
}

void SettingsDialog::on_settingsButtonBox_clicked(QAbstractButton *button) {
    if ((QPushButton *) button == ui->settingsButtonBox->button(QDialogButtonBox::Apply)) {
        saveSettings();
    }
}

void SettingsDialog::saveSettings() {
    int currentIndex = apiSettingsListWidgetItemList.indexOf(ui->apisListWidget->currentItem());

    if (currentIndex >= 0) {
        APISettings *apiSettings = appSettings->getApiSettingsList().at(currentIndex);
        apiSettings->setApiKey(ui->apiKeyLineEdit->text());
        apiSettings->setTextType(ui->textTypeLineEdit->text());
        apiSettings->setDefaultSourceLanguage(ui->defaultSourceLanguageLineEdit->text());
        apiSettings->setDefaultTargetLanguage(ui->defaultTargetLanguageLineEdit->text());
    }

    int defaultApiIndex = ui->defaultApiComboBox->currentIndex();
    QString defaultApiName = appSettings->getApiSettingsList().at(defaultApiIndex)->getName();
    appSettings->setDefaultApi(defaultApiName);

    appSettings->save();
}

void SettingsDialog::loadSettings() {
    for (int i = 0; i < appSettings->getApiSettingsList().count(); ++i) {
        APISettings *apiSettings = appSettings->getApiSettingsList().at(i);

        QListWidgetItem *listWidgetItem = new QListWidgetItem(apiSettings->getFullName());
        apiSettingsListWidgetItemList.append(listWidgetItem);
        ui->apisListWidget->addItem(listWidgetItem);

        ui->defaultApiComboBox->addItem(apiSettings->getFullName());
        QSettings settings;
        QString defaultApiName = settings.value("default_api").toString();
        if (apiSettings->getName() == defaultApiName) {
            ui->defaultApiComboBox->setCurrentIndex(i);
        }
    }
}
