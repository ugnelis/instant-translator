#include "microsoftapi.h"

MicrosoftAPI::MicrosoftAPI(QObject *parent)
        : API(parent) {
}

MicrosoftAPI::~MicrosoftAPI() {
}

QString MicrosoftAPI::translate(const QString &input,
                                const QString &sourceLanguage,
                                const QString &targetLanguage) const {
    if (input.isEmpty()) {
        return QString();
    }

    QSettings settings;
    QString key = settings.value("microsoft/key").toString();
    QString format = settings.value("microsoft/text_type").toString();

    // Format POST url string.
    QByteArray authorizationHeaderContent = "Bearer " + key.toUtf8();
    QString urlString = "https://api.cognitive.microsofttranslator.com/translate?api-version=3.0";
    urlString.append("&from=" + sourceLanguage);
    urlString.append("&to=" + targetLanguage);
    urlString.append("&format=" + format);

    // Format Json object.
    QJsonObject postJsonObject;
    postJsonObject["text"] = input;

    QJsonArray postJsonArray;
    postJsonArray.append(postJsonObject);

    QJsonDocument postJsonDocument(postJsonArray);

    QUrl url(urlString);
    QNetworkRequest request(url);
    request.setRawHeader("Ocp-Apim-Subscription-Key", key.toLocal8Bit());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    RequestManager requestManager(nullptr, manager);
    requestManager.postRequest(request, postJsonDocument.toJson());

    // Parse the replay.
    QByteArray replyByteArray = requestManager.getReply();

    QJsonDocument replyJsonDocument = QJsonDocument::fromJson(replyByteArray.data());

    if (replyJsonDocument.isObject()) {
        QJsonObject replyJsonObject = replyJsonDocument.object();

        // If error.
        if (replyJsonObject.contains("error")) {
            QJsonObject errorJsonObject = replyJsonObject["error"].toObject();
            int errorCode = errorJsonObject["code"].toInt();
            std::string errorMessage = errorJsonObject["message"]
                    .toString()
                    .toStdString();
            std::string exceptionMessage = "Error " + std::to_string(errorCode) + ": " + errorMessage;
            throw std::invalid_argument(exceptionMessage);
        }

        std::string exceptionMessage = "Something went wrong!";
        throw std::invalid_argument(exceptionMessage);
    }

    QJsonArray replyJsonArray = replyJsonDocument.array();

    qDebug() << replyJsonArray;

    QJsonArray translationsJsonArray = replyJsonArray[0]
            .toObject()["translations"]
            .toArray();

    QString translation;

    foreach (const QJsonValue &jsonValue, translationsJsonArray) {
        QJsonObject jsonObject = jsonValue.toObject();
        translation.append(jsonObject["text"].toString());
    }

    return translation;
}

QStringList MicrosoftAPI::getSupportedLanguages() const {
    QSettings settings;
    QString key = settings.value("microsoft/key").toString();

    // Format GET url string.
    QString urlString = "https://api.cognitive.microsofttranslator.com/languages?api-version=3.0";

    QUrl url(urlString);
    QNetworkRequest request(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    RequestManager requestManager(nullptr, manager);
    requestManager.getRequest(request);

    // Parse the replay.
    QByteArray replyByteArray = requestManager.getReply();

    QJsonDocument replyJsonDocument = QJsonDocument::fromJson(replyByteArray.data());
    QJsonObject replyJsonObject = replyJsonDocument.object();

    // If error.
    if (replyJsonObject.contains("error")) {
        QJsonObject errorJsonObject = replyJsonObject["error"].toObject();
        int errorCode = errorJsonObject["code"].toInt();
        std::string errorMessage = errorJsonObject["message"]
                .toString()
                .toStdString();
        std::string exceptionMessage = "Error " + std::to_string(errorCode) + ": " + errorMessage;
        throw std::invalid_argument(exceptionMessage);
    }

    QJsonObject translationJsonObject = replyJsonObject["translation"]
            .toObject();

    QStringList languagesList = translationJsonObject.keys();

    return languagesList;
}
