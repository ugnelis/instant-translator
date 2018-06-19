#ifndef INSTANT_TRANSLATOR_GOOGLEAPI_H
#define INSTANT_TRANSLATOR_GOOGLEAPI_H

#include <stdexcept>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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
    ~GoogleAPI() override;

    /**
     * Translate given input.
     * @param input Input string.
     * @param sourceLanguage Source language code.
     * @param targetLanguage Target language code.
     * @return Translated string.
     */
    QString translate(const QString &input,
                      const QString &sourceLanguage,
                      const QString &targetLanguage) const override;

    /**
     * Get supported languages.
     * @return Supported languages string list.
     */
    QStringList getSupportedLanguages() const override;
};

#endif // INSTANT_TRANSLATOR_GOOGLEAPI_H
