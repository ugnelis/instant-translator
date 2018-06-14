#include "apisettings.h"

APISettings::APISettings(QObject *parent)
        : QObject(parent) {
}

APISettings::APISettings(QObject *parent, const QString &name, const QString &fullName)
        : QObject(parent), name(name), fullName(fullName) {
}

APISettings::~APISettings() {
}

void APISettings::readSettings() {
    if (name == "") {
        throw std::invalid_argument("API name has not been set.");
    }
    QSettings settings;
    apiKey = settings.value(name + "/key", "API_KEY").toString();
    textType = settings.value(name + "/text_type", "text").toString();
    defaultSourceLanguage = settings.value(name + "/source", "lt").toString();
    defaultTargetLanguage = settings.value(name + "/target", "en").toString();
}

void APISettings::writeSettings() {
    if (name == "") {
        throw std::invalid_argument("API name has not been set.");
    }
    QSettings settings;
    settings.setValue(name + "/key", apiKey);
    settings.setValue(name + "/text_type", textType);
    settings.setValue(name + "/source", defaultSourceLanguage);
    settings.setValue(name + "/target", defaultTargetLanguage);
}

QString APISettings::getName() const {
    return name;
}

void APISettings::setName(const QString &name) {
    this->name = name;
}

QString APISettings::getFullName() const {
    return fullName;
}

void APISettings::setFullName(const QString &fullName) {
    this->fullName = fullName;
}

QString APISettings::getApiKey() const {
    return apiKey;
}

void APISettings::setApiKey(const QString &apiKey) {
    this->apiKey = apiKey;
}

QString APISettings::getTextType() const {
    return textType;
}

void APISettings::setTextType(const QString &textType) {
    this->textType = textType;
}

QString APISettings::getDefaultSourceLanguage() const {
    return defaultSourceLanguage;
}

void APISettings::setDefaultSourceLanguage(const QString &defaultSourceLanguage) {
    this->defaultSourceLanguage = defaultSourceLanguage;
}

QString APISettings::getDefaultTargetLanguage() const {
    return defaultTargetLanguage;
}

void APISettings::setDefaultTargetLanguage(const QString &defaultTargetLanguage) {
    this->defaultTargetLanguage = defaultTargetLanguage;
}
