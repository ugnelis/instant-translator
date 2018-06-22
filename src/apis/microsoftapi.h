#ifndef INSTANT_TRANSLATOR_MICROSOFTAPI_H
#define INSTANT_TRANSLATOR_MICROSOFTAPI_H

#include <stdexcept>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "api.h"
#include "utils/requestmanager.h"

/**
 * Microsoft Translator API implementation class.
 */
class MicrosoftAPI : public API {
public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     */
    explicit MicrosoftAPI(QObject *parent = nullptr);

    /**
     * Destructor.
     */
    ~MicrosoftAPI() override;

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

#endif // INSTANT_TRANSLATOR_MICROSOFTAPI_H
