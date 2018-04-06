#ifndef INSTANT_TRANSLATOR_LANGUAGE_H
#define INSTANT_TRANSLATOR_LANGUAGE_H

#include <QHash>
#include <QString>
#include <QIODevice>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

/**
 * Language codes and names holder.
 */
class Language {
public:
    /**
     * Constructor.
     */
    Language();

    /**
     * Destructor.
     */
    ~Language();

    /**
     * Get language name.
     * @param code Language code.
     * @return Language name.
     */
    QString getName(QString code);

    /**
     * Get language code.
     * @param name Language name.
     * @return Language code.
     */
    QString getCode(QString name);

private:
    /**
     * Read language code and name from JSON file.
     * @param jsonFile JSON file path.
     */
    void readFromJsonFile(QString jsonFile = ":/resources/languages.json");

    QHash<QString, QString> hash; // <language code, language name>.
};


#endif //INSTANT_TRANSLATOR_LANGUAGE_H
