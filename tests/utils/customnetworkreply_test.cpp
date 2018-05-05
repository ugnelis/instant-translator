#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QList>
#include <QNetworkReply>
#include "utils/customnetworkreply.h"

TEST(CustomNetworkReplyTests, setContentType_CheckContentType_True) {
    CustomNetworkReply reply;
    reply.setContentType("application/json");
    QList<QNetworkReply::RawHeaderPair> rawHeaderList = reply.rawHeaderPairs();

    ASSERT_EQ("application/json", rawHeaderList.at(0).second);
}

TEST(CustomNetworkReplyTests, setContent_GiveQStringAsAValue_True) {
    CustomNetworkReply reply;
    reply.setContent(QString("This is test!"));
    QByteArray content = reply.readAll();

    ASSERT_EQ(QString("This is test!"), content);
}

TEST(CustomNetworkReplyTests, setContent_GiveQByteArrayAsAValue_True) {
    CustomNetworkReply reply;
    reply.setContent(QByteArray("This is test!"));
    QByteArray content = reply.readAll();

    ASSERT_EQ(QString("This is test!"), content);
}

TEST(CustomNetworkReplyTests, abort_DoNotDoAnything_True) {
    CustomNetworkReply reply;
    reply.setContent(QByteArray(""));
    QByteArray content = reply.readAll();
    reply.abort();

    ASSERT_EQ(QString(""), content);
}

TEST(CustomNetworkReplyTests, bytesAvailable_CheckBytes_True) {
    CustomNetworkReply reply;
    reply.setContent(QByteArray("This is test!"));

    qint64 bytesAvailable = reply.bytesAvailable();

    ASSERT_EQ(13, bytesAvailable);
}

TEST(CustomNetworkReplyTests, isSequential_CheckIfItIsSequeantial_True) {
    CustomNetworkReply reply;
    bool isSequential = reply.isSequential();

    ASSERT_EQ(true, isSequential);
}
