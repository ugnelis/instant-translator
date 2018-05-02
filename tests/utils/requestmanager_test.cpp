#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include "utils/requestmanager.h"
#include "utils/customnetworkreply.h"
#include <QDebug>

class MockQNetworkAccessManager : public QNetworkAccessManager {
public:
    MockQNetworkAccessManager(QObject *parent = nullptr) : QNetworkAccessManager(parent) {}

protected:
    QNetworkReply *createRequest(Operation op, const QNetworkRequest &originalReq,
                                 QIODevice *outgoingData = Q_NULLPTR) override {
        CustomNetworkReply *reply = new CustomNetworkReply();
        reply->setHttpStatusCode(200, "OK");
        reply->setContentType("application/json");
        reply->setContent(QString("{\"data\":{\"translations\":[{\"translatedText\":\"Hello\"}]}}"));

        return reply;
    }
};

TEST(RequestManagerTests, postRequest_SendPostRequest_True) {
    int argc = 0;
    char **argv = 0;
    QApplication app(argc, argv);

    // Format Json object.
    QJsonObject postJsonObject;
    postJsonObject["source"] = "lt";
    postJsonObject["target"] = "en";
    postJsonObject["format"] = "text";
    postJsonObject["q"] = "Labas";

    QJsonDocument postJsonDocument(postJsonObject);

    // Make request.
    QUrl url("https://randomurl.com/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Send request.
    MockQNetworkAccessManager *manager = new MockQNetworkAccessManager();

    RequestManager requestManager(nullptr, manager);
    requestManager.postRequest(request, postJsonDocument.toJson());

    // Test.
    QString expexted = "{\"data\":{\"translations\":[{\"translatedText\":\"Hello\"}]}}";
    ASSERT_EQ(expexted, requestManager.getReply());
}
