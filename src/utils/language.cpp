#include "language.h"
#include <QDebug>

Language::Language() {
    readFromJsonFile();
}

Language::~Language() {
}

QString Language::getName(QString code) {
    return hash.value(code);
}

QString Language::getCode(QString name) {
    return hash.key(name);
}

QStringList Language::getLanguages(QStringList codeList) {
    QStringList nameList;
    foreach (QString code, codeList) {
        nameList.append(hash.value(code));
    }
    return nameList;
}

QStringList Language::getCodes(QStringList nameList) {
    QStringList codeList;
    foreach (QString name, nameList) {
        codeList.append(hash.key(name));
    }
    return codeList;
}

void Language::readFromJsonFile(QString jsonFile) {
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
