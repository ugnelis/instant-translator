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
    QString key = settings.value("temp/key").toString();
    QString format = settings.value("temp/text_type").toString();

    QString translation = "Some translation.";

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
    QString helloWorld = domNodeList.at(0).toElement().text();

    QStringList languagesList;
    for (int i = 0; i < domNodeList.count(); ++i) {
        languagesList.append(domNodeList.at(i).toElement().text());
    }

    // TODO(Ugnelis): catch the error.

    return languagesList;
}
