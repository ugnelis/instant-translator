#ifndef INSTANT_TRANSLATOR_APISETTINGS_H
#define INSTANT_TRANSLATOR_APISETTINGS_H

#include <stdexcept>
#include <QObject>
#include <QString>
#include <QSettings>

/**
 * API settings holder class.
 */
class APISettings : public QObject {
public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     */
    explicit APISettings(QObject *parent = nullptr);

    /**
     * Constructs an object with parent object parent.
     * @param parent parent Parent of an object may be viewed as the object's owner.
     * @param name API name.
     * @param fullName API full name.
     */
    APISettings(QObject *parent, const QString &name, const QString &fullName);

    /**
     * Destructor.
     */
    ~APISettings() override;

    /**
     * Read API settings to app settings.
     */
    void readSettings();

    /**
     * Write API settings to app settings.
     */
    void writeSettings();

    /**
     * Get API name.
     * @return API name.
     */
    QString getName() const;

    /**
     * Set API name.
     * @param name API name.
     */
    void setName(const QString &name);

    /**
     * Get API full name.
     * @return API full name.
     */
    QString getFullName() const;

    /**
     * Set API full name.
     * @param fullName API full name.
     */
    void setFullName(const QString &fullName);

    /**
     * Get API key.
     * @return API key.
     */
    QString getApiKey() const;

    /**
     * Set API key.
     * @param apiKey API key.
     */
    void setApiKey(const QString &apiKey);

    /**
     * Get translation text type.
     * @return Translation text type.
     */
    QString getTextType() const;

    /**
     * Set translation text type.
     * @param textType Translation text type.
     */
    void setTextType(const QString &textType);

    /**
     * Get default source language code.
     * @return Default source language code.
     */
    QString getDefaultSourceLanguage() const;

    /**
     * Set default source language code.
     * @param defaultSourceLanguage Default source language code.
     */
    void setDefaultSourceLanguage(const QString &defaultSourceLanguage);

    /**
     * Get default target language code.
     * @return Default target language code.
     */
    QString getDefaultTargetLanguage() const;

    /**
     * Set default target language code.
     * @param defaultTargetLanguage Default target language code.
     */
    void setDefaultTargetLanguage(const QString &defaultTargetLanguage);

private:
    QString name;
    QString fullName;
    QString apiKey;
    QString textType;
    QString defaultSourceLanguage;
    QString defaultTargetLanguage;
};


#endif //INSTANT_TRANSLATOR_APISETTINGS_H
