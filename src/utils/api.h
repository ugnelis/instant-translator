#ifndef INSTANT_TRANSLATOR_API_H
#define INSTANT_TRANSLATOR_API_H

#include <QObject>
#include <QString>
#include <QStringList>

/**
 * Abstract class for API classes.
 */
class API : public QObject {
Q_OBJECT
public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     */
    explicit API(QObject *parent = nullptr);

    /**
     * Translate given input.
     * @param input Input string.
     * @return Output string.
     */
    virtual QString translate(const QString &input) = 0;

    /**
     * Get supported languages.
     * @return Supported languages string list.
     */
    virtual QStringList getSupportedLanguages() = 0;
};

#endif // INSTANT_TRANSLATOR_API_H
