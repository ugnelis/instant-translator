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

    // Format GET url string.
    QByteArray authorizationHeaderContent = "Bearer " + key.toUtf8();
    QString urlString = "https://api.microsofttranslator.com/V2/Http.svc/Translate?";
    urlString.append("&from=" + sourceLanguage);
    urlString.append("&to=" + targetLanguage);
    urlString.append("&format=" + format);
    urlString.append("&text=" + input);

    QUrl url(urlString);
    QNetworkRequest request(url);
    request.setRawHeader("Ocp-Apim-Subscription-Key", key.toLocal8Bit());

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    RequestManager requestManager(nullptr, manager);
    requestManager.getRequest(request);

    // Parse the replay.
    QByteArray replyByteArray = requestManager.getReply();

    QDomDocument domDocument;
    domDocument.setContent(replyByteArray);
    QDomNodeList domNodeList = domDocument.elementsByTagName("string");

    QString translation;
    for (int i = 0; i < domNodeList.count(); ++i) {
        translation.append(domNodeList.at(i).toElement().text());
    }

    // TODO(Ugnelis): catch the error.

    return translation;
}

QStringList MicrosoftAPI::getSupportedLanguages() const {
    QSettings settings;
    QString key = settings.value("microsoft/key").toString();

    // Format GET url string.
    QString urlString = "https://api.microsofttranslator.com/V2/Http.svc/GetLanguagesForTranslate";

    QUrl url(urlString);
    QNetworkRequest request(url);
    request.setRawHeader("Ocp-Apim-Subscription-Key", key.toLocal8Bit());

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    RequestManager requestManager(nullptr, manager);
    requestManager.getRequest(request);

    // Parse the replay.
    QByteArray replyByteArray = requestManager.getReply();

    QDomDocument domDocument;
    domDocument.setContent(replyByteArray);
    QDomNodeList domNodeList = domDocument.elementsByTagName("string");

    QStringList languagesList;
    for (int i = 0; i < domNodeList.count(); ++i) {
        languagesList.append(domNodeList.at(i).toElement().text());
    }

    // TODO(Ugnelis): catch the error.

    return languagesList;
}
