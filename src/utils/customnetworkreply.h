#ifndef INSTANT_TRANSLATOR_CUSTOMNETWORKREPLY_H
#define INSTANT_TRANSLATOR_CUSTOMNETWORKREPLY_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBuffer>
#include <QTimer>

/**
 * Custom QNetworkReply class.
 */
class CustomNetworkReply : public QNetworkReply {
Q_OBJECT

public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     */
    explicit CustomNetworkReply(QObject *parent = nullptr);

    /**
     * Destructor.
     */
    ~CustomNetworkReply() override;

    /**
     *
     * @param code
     * @param statusText
     */
    void setHttpStatusCode(int code, const QByteArray &statusText = QByteArray());

    /**
     * Sets the value of the known header header to be
     * value, overriding any previously set headers.
     * @param header Header.
     * @param value Value.
     */
    void setHeader(QNetworkRequest::KnownHeaders header, const QVariant &value);

    /**
     * Set content type, e.g., "text/html".
     * @param contentType Content type.
     */
    void setContentType(const QByteArray &contentType);

    /**
     * Set content.
     * @param content Content.
     */
    void setContent(const QString &content);

    /**
     * Set content.
     * @param content Content.
     */
    void setContent(const QByteArray &content);

    /**
     * Aborts the operation immediately and close
     * down any network connections still open.
     */
    void abort() override;

    /**
     * Returns the number of bytes that are available for reading.
     * @return Bytes that are available for reading.
     */
    qint64 bytesAvailable() const override;

    /**
     * Returns true if this device is sequential; otherwise returns false.
     * @return Returns true if this device is sequential.
     */
    bool isSequential() const override;

protected:
    /**
     * Reads up to maxSize bytes from the device into data, and
     * returns the number of bytes read or -1 if an error occurred.
     * @param data Data.
     * @param maxSize Max size.
     * @return returns the number of bytes read or -1 if an error occurred.
     */
    qint64 readData(char *data, qint64 maxSize) override;

private:
    QByteArray content;
    qint64 offset;
};

#endif //INSTANT_TRANSLATOR_CUSTOMNETWORKREPLY_H
