#ifndef INSTANT_TRANSLATOR_REQUESTMANAGER_H
#define INSTANT_TRANSLATOR_REQUESTMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

/**
 * Request manager class.
 */
class RequestManager : public QObject {
Q_OBJECT
public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     * @param manager Network access manager.
     */
    RequestManager(QObject *parent, QNetworkAccessManager *manager);

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
    QNetworkAccessManager *manager; // Network manager.
    QByteArray networkReplyData; // Network reply data.
};

#endif //INSTANT_TRANSLATOR_REQUESTMANAGER_H
