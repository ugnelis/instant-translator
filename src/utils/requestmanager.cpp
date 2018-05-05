#include "requestmanager.h"

RequestManager::RequestManager(QObject *parent, std::unique_ptr<QNetworkAccessManager> manager)
        : QObject(parent), manager(std::move(manager)) {
}

RequestManager::~RequestManager() {
}

void RequestManager::postRequest(const QNetworkRequest &request, const QByteArray &data) {
    networkReply = manager->post(request, data);

    // Wait for the reply.
    QEventLoop loop;
    connect(
            networkReply,
            SIGNAL(finished()),
            &loop,
            SLOT(quit())
    );
    loop.exec();
}

void RequestManager::getRequest(const QNetworkRequest &request) {
    networkReply = manager->get(request);

    // Wait for the reply.
    QEventLoop loop;
    connect(
            networkReply,
            SIGNAL(finished()),
            &loop,
            SLOT(quit())
    );
    loop.exec();
}

QByteArray RequestManager::getReply() {
    if (networkReply == nullptr) {
        return QByteArray();
    }
    return networkReply->readAll();
}
