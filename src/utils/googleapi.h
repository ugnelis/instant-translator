#ifndef INSTANT_TRANSLATOR_GOOGLEAPI_H
#define INSTANT_TRANSLATOR_GOOGLEAPI_H

#include <string>
#include <QObject>
#include <QSettings>
#include <QJsonObject>
#include <QJsonDocument>
#include "api.h"
#include "utils/requestmanager.h"

/**
 * Google Translate API implementation class.
 */
class GoogleAPI : public API {
public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     */
    explicit GoogleAPI(QObject *parent = nullptr);

    /**
     * Destructor.
     */
    ~GoogleAPI();

    /**
     * Translate given input.
     * @param input input string.
     * @return output string.
     */
    QString translate(const QString &input) override;

private:
    RequestManager *requestManager;
};

#endif // INSTANT_TRANSLATOR_GOOGLEAPI_H
