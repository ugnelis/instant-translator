#ifndef INSTANT_TRANSLATOR_REQUESTMANAGER_H
#define INSTANT_TRANSLATOR_REQUESTMANAGER_H

#include <memory>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

class RequestManager : public QObject {
Q_OBJECT
public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     * @param manager Network access manager.
     */
    RequestManager(QObject *parent, std::unique_ptr<QNetworkAccessManager> manager);

    /**
     * Destructor.
     */
    ~RequestManager() override;

    /**
     * Send POST request.
     * @param request Request.
     * @param data Data.
     */
    void postRequest(const QNetworkRequest &request, const QByteArray &data);

    /**
     * Send GET request.
     * @param request Request.
     */
    void getRequest(const QNetworkRequest &request);

    /**
     * Get reply from the request.
     * @return
     */
    QByteArray getReply();

private:
    std::unique_ptr<QNetworkAccessManager> manager; // Network manager.
    QNetworkReply *networkReply; // Network reply.
};

#endif //INSTANT_TRANSLATOR_REQUESTMANAGER_H
