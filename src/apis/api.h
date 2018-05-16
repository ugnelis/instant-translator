#ifndef INSTANT_TRANSLATOR_API_H
#define INSTANT_TRANSLATOR_API_H

#include <QtPlugin>
#include <QString>
#include <QStringList>

/**
 * Abstract class for API classes.
 */
class API {
public:
    /**
     * Destructor.
     */
    virtual ~API() {}

    /**
     * Translate given input.
     * @param input Input string.
     * @param sourceLanguage Source language code.
     * @param targetLanguage Target language code.
     * @return Translated string.
     */
    virtual QString translate(const QString &input,
                              const QString &sourceLanguage,
                              const QString &targetLanguage) const = 0;

    /**
     * Get supported languages.
     * @return Supported languages string list.
     */
    virtual QStringList getSupportedLanguages() const = 0;
};

Q_DECLARE_INTERFACE(API, "API")

#endif // INSTANT_TRANSLATOR_API_H
