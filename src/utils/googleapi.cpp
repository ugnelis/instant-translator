#include "googleapi.h"

GoogleAPI::GoogleAPI(QObject *parent)
        : API(parent), requestManager(new RequestManager(this)) {
}

GoogleAPI::~GoogleAPI() {
    delete requestManager;
}

QString GoogleAPI::translate(const QString &input) {
    if (input.isEmpty()) {
        return QString();
    }

    QSettings settings;
    QString key = settings.value("api/google/key").toString();
    QString source = settings.value("source").toString();
    QString target = settings.value("target").toString();
    QString format = settings.value("format").toString();

    // Format GET url string.
    QByteArray authorizationHeaderContent = "Bearer " + key.toUtf8();
    QString urlString = "https://www.googleapis.com/language/translate/v2?";
    urlString.append("&key=" + key);
    urlString.append("&source=" + source);
    urlString.append("&target=" + target);
    urlString.append("&format=" + format);
    urlString.append("&q=" + input);

    QUrl url(urlString);
    QNetworkRequest request(url);

    RequestManager *requestManager = new RequestManager(this);
    requestManager->getRequest(request);

    // Parse the replay.
    QByteArray replyByteArray = requestManager->getReply();

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
