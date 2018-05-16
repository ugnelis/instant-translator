#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include "utils/requestmanager.h"
#include "utils/customnetworkreply.h"

class MockQNetworkAccessManager : public QNetworkAccessManager {
public:
    explicit MockQNetworkAccessManager(QObject *parent = nullptr) : QNetworkAccessManager(parent) {}

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
    QCoreApplication app(argc, argv);

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
    QString expected = "{\"data\":{\"translations\":[{\"translatedText\":\"Hello\"}]}}";
    ASSERT_EQ(expected, requestManager.getReply());
}

TEST(RequestManagerTests, getRequest_SendGetRequest_True) {
    int argc = 0;
    char **argv = 0;
    QCoreApplication app(argc, argv);

    // Make request.
    QUrl url("https://randomurl.com/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Send request.
    MockQNetworkAccessManager *manager = new MockQNetworkAccessManager();

    RequestManager requestManager(nullptr, manager);
    requestManager.getRequest(request);

    // Test.
    QString expected = "{\"data\":{\"translations\":[{\"translatedText\":\"Hello\"}]}}";
    ASSERT_EQ(expected, requestManager.getReply());
}

TEST(RequestManagerTests, getReply_NetworkReplyIsNull_True) {
    int argc = 0;
    char **argv = 0;
    QCoreApplication app(argc, argv);

    // Make request.
    QUrl url("https://randomurl.com/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Send request.
    MockQNetworkAccessManager *manager = new MockQNetworkAccessManager();

    RequestManager requestManager(nullptr, manager);

    // Test.
    QByteArray expected("");
    ASSERT_EQ(expected, requestManager.getReply());
}
