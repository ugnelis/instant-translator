#include "googleapi.h"

GoogleAPI::GoogleAPI(QObject *parent)
        : QObject(parent) {
}

GoogleAPI::~GoogleAPI() {
}

QString GoogleAPI::translate(const QString &input,
                             const QString &sourceLanguage,
                             const QString &targetLanguage) const {
    if (input.isEmpty()) {
        return QString();
    }

    QSettings settings(":/resources/configs/api.ini", QSettings::IniFormat);
    QString key = settings.value("google/key").toString();
    QString format = settings.value("google/format").toString();

    // Format POST url string.
    QString urlString = "https://translation.googleapis.com/language/translate/v2?";
    urlString.append("key=" + key);

    // Format Json object.
    QJsonObject postJsonObject;
    postJsonObject["source"] = sourceLanguage;
    postJsonObject["target"] = targetLanguage;
    postJsonObject["format"] = format;
    postJsonObject["q"] = input;

    QJsonDocument postJsonDocument(postJsonObject);

    QUrl url(urlString);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    QNetworkAccessManager *manager = new QNetworkAccessManager();

    RequestManager requestManager(nullptr, std::move(manager));
    requestManager.postRequest(request, postJsonDocument.toJson());

    // Parse the replay.
    QByteArray replyByteArray = requestManager.getReply();

    QJsonDocument replyJsonDocument = QJsonDocument::fromJson(replyByteArray.data());
    QJsonObject replyJsonObject = replyJsonDocument.object();

    QJsonArray translationsJsonArray = replyJsonObject["data"]
            .toObject()["translations"]
            .toArray();

    QString translation;

    foreach (const QJsonValue &jsonValue, translationsJsonArray) {
        QJsonObject jsonObject = jsonValue.toObject();
        translation.append(jsonObject["translatedText"].toString());
    }

    return translation;
}

QStringList GoogleAPI::getSupportedLanguages() const {
    QSettings settings(":/resources/configs/api.ini", QSettings::IniFormat);
    QString key = settings.value("google/key").toString();

    // Format GET url string.
    QString urlString = "https://translation.googleapis.com/language/translate/v2/languages?";
    urlString.append("key=" + key);

    QUrl url(urlString);
    QNetworkRequest request(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    RequestManager requestManager(nullptr, std::move(manager));
    requestManager.getRequest(request);

    // Parse the replay.
    QByteArray replyByteArray = requestManager.getReply();

    QJsonDocument replyJsonDocument = QJsonDocument::fromJson(replyByteArray.data());
    QJsonObject replyJsonObject = replyJsonDocument.object();

    QJsonArray languagesJsonArray = replyJsonObject["data"]
            .toObject()["languages"]
            .toArray();

    QStringList languagesList;

    // Add languages to list.
    foreach (const QJsonValue &jsonValue, languagesJsonArray) {
        QJsonObject jsonObject = jsonValue.toObject();
        languagesList.append(jsonObject["language"].toString());
    }

    return languagesList;
}
