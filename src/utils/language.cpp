#include "language.h"

Language::Language(QObject *parent)
        : QObject(parent) {
    readFromJsonFile();
}

Language::~Language() {
}

QString Language::getName(const QString &code) const {
    return hash.value(code);
}

QString Language::getCode(const QString &name) const {
    return hash.key(name);
}

QStringList Language::getLanguages(const QStringList &codeList) const {
    QStringList nameList;
    foreach (QString code, codeList) {
        nameList.append(hash.value(code));
    }
    return nameList;
}

QStringList Language::getCodes(const QStringList &nameList) const {
    QStringList codeList;
    foreach (QString name, nameList) {
        codeList.append(hash.key(name));
    }
    return codeList;
}

void Language::readFromJsonFile(const QString &jsonFile) {
    // Read JSON file.
    QString jsonString;
    QFile file;
    file.setFileName(jsonFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonString = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray jsonArray = jsonDocument.array();
    foreach (const QJsonValue &jsonValue, jsonArray) {
        QJsonObject jsonObject = jsonValue.toObject();
        QString key = jsonObject["code"].toString();
        QString value = jsonObject["name"].toString();
        hash[key] = value;
    }
}
