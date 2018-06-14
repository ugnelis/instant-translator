#include "tempapi.h"

TempAPI::TempAPI(QObject *parent)
        : QObject(parent) {
}

TempAPI::~TempAPI() {
}

QString TempAPI::translate(const QString &input,
                           const QString &sourceLanguage,
                           const QString &targetLanguage) const {
    if (input.isEmpty()) {
        return QString();
    }

    QSettings settings;
    QString key = settings.value("temp/key").toString();
    QString format = settings.value("temp/format").toString();

    QString translation = "Some translation.";

    return translation;
}

QStringList TempAPI::getSupportedLanguages() const {
    QSettings settings;
    QString key = settings.value("temp/key").toString();

    QStringList languagesList;

    languagesList.append("en");
    languagesList.append("fr");
    languagesList.append("de");
    languagesList.append("lt");

    return languagesList;
}
