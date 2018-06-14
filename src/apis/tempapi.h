#ifndef INSTANT_TRANSLATOR_TEMPAPI_H
#define INSTANT_TRANSLATOR_TEMPAPI_H

#include <QObject>
#include <QSettings>
#include "api.h"

/**
 * Temporary API implementation class.
 */
class TempAPI : public QObject, public API {
Q_OBJECT
Q_INTERFACES(API)
public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     */
    explicit TempAPI(QObject *parent = nullptr);

    /**
     * Destructor.
     */
    ~TempAPI() override;

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

#endif // INSTANT_TRANSLATOR_TEMPAPI_H
