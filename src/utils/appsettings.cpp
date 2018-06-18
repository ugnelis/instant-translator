#include "appsettings.h"

AppSettings::AppSettings(QObject *parent)
        : QObject(parent), defaultApi(nullptr) {
}

AppSettings::~AppSettings() {
}

void AppSettings::addApiSettings(APISettings *apiSettings) {
    apiSettings->readSettings();
    apiSettingsList.append(apiSettings);
}

QList<APISettings *> AppSettings::getApiSettingsList() const {
    return apiSettingsList;
}

void AppSettings::setDefaultApi(APISettings *apiSettings) {
    int index = apiSettingsList.indexOf(apiSettings);

    if (index < 0) {
        apiSettingsList.append(apiSettings);
    }
    defaultApi = apiSettings;
}

void AppSettings::setDefaultApi(QString name) {
    for (int i = 0; i < apiSettingsList.count(); ++i) {
        if (apiSettingsList.at(i)->getName() == name) {
            defaultApi = apiSettingsList.at(i);
            return;
        }
    }

    std::string exceptionMessage = "API with name '" + name.toStdString() + "' does not exist.";
    throw std::invalid_argument(exceptionMessage);
}

APISettings *AppSettings::getDefaultApi() {
    return defaultApi;
}

void AppSettings::save() {
    for (int i = 0; i < apiSettingsList.count(); ++i) {
        APISettings *apiSettings = apiSettingsList.at(i);
        apiSettings->writeSettings();
    }

    if (defaultApi != nullptr) {
        QSettings settings;
        settings.setValue("default_api", defaultApi->getName());
    }
}
