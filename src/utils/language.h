#ifndef INSTANT_TRANSLATOR_LANGUAGE_H
#define INSTANT_TRANSLATOR_LANGUAGE_H

#include <QHash>
#include <QString>
#include <QStringList>
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

    /**
     * Get the names of the languages.
     * @param codeList Language code list.
     * @return Language name list.
     */
    QStringList getLanguages(QStringList codeList);

    /**
     * Get the codes of the languages.
     * @param nameList Language name list.
     * @return codeList Language code list.
     */
    QStringList getCodes(QStringList nameList);

private:
    /**
     * Read language code and name from JSON file.
     * @param jsonFile JSON file path.
     */
    void readFromJsonFile(QString jsonFile = ":/resources/languages.json");

    QHash<QString, QString> hash; // <language code, language name>.
};


#endif //INSTANT_TRANSLATOR_LANGUAGE_H
