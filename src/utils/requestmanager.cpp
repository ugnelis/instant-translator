#include "requestmanager.h"

RequestManager::RequestManager(QObject *parent)
        : QObject(parent), manager(new QNetworkAccessManager), networkReplyData(QByteArray("")) {
}

RequestManager::RequestManager(QObject *parent, QNetworkAccessManager *manager)
        : QObject(parent), manager(manager), networkReplyData(QByteArray("")) {
}

RequestManager::~RequestManager() {
    delete manager;
}

void RequestManager::postRequest(const QNetworkRequest &request, const QByteArray &data) {
    QNetworkReply *networkReply = manager->post(request, data);

    // Wait for the reply.
    QEventLoop loop;
    connect(
            networkReply,
            SIGNAL(finished()),
            &loop,
            SLOT(quit())
    );
    loop.exec();

    networkReplyData = networkReply->readAll();
}

void RequestManager::getRequest(const QNetworkRequest &request) {
    QNetworkReply *networkReply = manager->get(request);

    // Wait for the reply.
    QEventLoop loop;
    connect(
            networkReply,
            SIGNAL(finished()),
            &loop,
            SLOT(quit())
    );
    loop.exec();

    networkReplyData = networkReply->readAll();
}

QByteArray RequestManager::getReply() {
    return networkReplyData;
}
