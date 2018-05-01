#include "customnetworkreply.h"

CustomNetworkReply::CustomNetworkReply(QObject *parent)
        : QNetworkReply(parent), content(nullptr), offset(0) {
}

CustomNetworkReply::~CustomNetworkReply() {
}

void CustomNetworkReply::setHttpStatusCode(int code, const QByteArray &statusText) {
    setAttribute(QNetworkRequest::HttpStatusCodeAttribute, code);
    if (statusText.isNull())
        return;

    setAttribute(QNetworkRequest::HttpReasonPhraseAttribute, statusText);
}

void CustomNetworkReply::setHeader(QNetworkRequest::KnownHeaders header, const QVariant &value) {
    QNetworkReply::setHeader(header, value);
}

void CustomNetworkReply::setContentType(const QByteArray &contentType) {
    setHeader(QNetworkRequest::ContentTypeHeader, contentType);
}

void CustomNetworkReply::setContent(const QString &content) {
    setContent(content.toUtf8());
}

void CustomNetworkReply::setContent(const QByteArray &content) {
    this->content = content;
    offset = 0;

    open(ReadOnly | Unbuffered);
    setHeader(QNetworkRequest::ContentLengthHeader, QVariant(content.size()));

    QTimer::singleShot(0, this, SIGNAL(readyRead()));
    QTimer::singleShot(0, this, SIGNAL(finished()));
}

void CustomNetworkReply::abort() {
    // No operation.
}

qint64 CustomNetworkReply::bytesAvailable() const {
    return content.size() - offset + QIODevice::bytesAvailable();
}

bool CustomNetworkReply::isSequential() const {
    return true;
}

qint64 CustomNetworkReply::readData(char *data, qint64 maxSize) {
    if (offset >= content.size())
        return -1;

    qint64 number = qMin(maxSize, content.size() - offset);
    memcpy(data, content.constData() + offset, number);
    offset += number;

    return number;
}
