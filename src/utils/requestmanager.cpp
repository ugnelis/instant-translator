#include <QDebug>
#include "requestmanager.h"

RequestManager::RequestManager(QObject *parent)
        : QObject(parent), manager(new QNetworkAccessManager) {
}

RequestManager::~RequestManager() {
    delete manager;
}

void RequestManager::postRequest(QNetworkRequest request, QByteArray data) {
    QObject::connect(manager, SIGNAL(finished(QNetworkReply * )),
                     this, SLOT(onGetReply(QNetworkReply * )));
    manager->post(request, data);
}

void RequestManager::getRequest(QNetworkRequest request) {
    QObject::connect(manager, SIGNAL(finished(QNetworkReply * )),
                     this, SLOT(onGetReply(QNetworkReply * )));
    manager->get(request);
}

QByteArray RequestManager::getReply() {
    return data;
}

void RequestManager::onGetReply(QNetworkReply *reply) {
    data = reply->readAll();
}
