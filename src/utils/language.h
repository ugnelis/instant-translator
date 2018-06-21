#ifndef INSTANT_TRANSLATOR_LANGUAGE_H
#define INSTANT_TRANSLATOR_LANGUAGE_H

#include <QObject>
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
class Language : public QObject {
public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     */
    explicit Language(QObject *parent = nullptr);

    /**
     * Destructor.
     */
    ~Language() override;

    /**
     * Get language name.
     * @param code Language code.
     * @return Language name.
     */
    QString getName(const QString &code) const;

    /**
     * Get language code.
     * @param name Language name.
     * @return Language code.
     */
    QString getCode(const QString &name) const;

    /**
     * Get the names of the languages.
     * @param codeList Language code list.
     * @return Language name list.
     */
    QStringList getLanguages(const QStringList &codeList) const;

    /**
     * Get the codes of the languages.
     * @param nameList Language name list.
     * @return codeList Language code list.
     */
    QStringList getCodes(const QStringList &nameList) const;

private:
    /**
     * Read language code and name from JSON file.
     * @param jsonFile JSON file path.
     */
    void readFromJsonFile(const QString &jsonFile = ":/resources/languages.json");

    QHash<QString, QString> hash; // <language code, language name>.
};


#endif //INSTANT_TRANSLATOR_LANGUAGE_H
