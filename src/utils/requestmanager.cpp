#include "requestmanager.h"

RequestManager::RequestManager(QObject *parent)
        : QObject(parent), manager(new QNetworkAccessManager) {
}

RequestManager::~RequestManager() {
    delete manager;
}

void RequestManager::postRequest(const QNetworkRequest &request, const QByteArray &data) {
    QObject::connect(manager, SIGNAL(finished(QNetworkReply * )),
                     this, SLOT(onGetReply(QNetworkReply * )));
    networkReply = manager->post(request, data);

    // Wait for the reply.
    QEventLoop loop;
    connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

void RequestManager::getRequest(const QNetworkRequest &request) {
    networkReply = manager->get(request);

    // Wait for the reply.
    QEventLoop loop;
    connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

QByteArray RequestManager::getReply() {
    if (networkReply == nullptr) {
        return QByteArray();
    }
    return networkReply->readAll();
}
