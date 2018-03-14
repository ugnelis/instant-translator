#include <QSettings>
#include <QDebug>
#include "googleapi.h"

GoogleAPI::GoogleAPI() {
    QSettings settings;
    QString key = settings.value("api/google/key").toString();
    qDebug() << key;
}

GoogleAPI::~GoogleAPI() {
}

std::string GoogleAPI::translate(const std::string &input) const {
    return "output";
}
