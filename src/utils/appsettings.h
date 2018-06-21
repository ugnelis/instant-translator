#ifndef INSTANT_TRANSLATOR_APPSETTINGS_H
#define INSTANT_TRANSLATOR_APPSETTINGS_H

#include <stdexcept>
#include <QObject>
#include <QString>
#include <QSettings>
#include "utils/apisettings.h"

/**
 * App settings holder class.
 */
class AppSettings : public QObject {
public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     */
    explicit AppSettings(QObject *parent = nullptr);

    /**
     * Destructor.
     */
    ~AppSettings() override;

    /**
     * Add API settings.
     * @param apiSettings API settings.
     */
    void addApiSettings(APISettings *apiSettings);

    /**
     * Get API settings list.
     * @return API settings list.
     */
    QList<APISettings *> getApiSettingsList() const;

    /**
     * Set default API. If API doesn't exists, it is being add.
     * @param apiSettings API settings.
     */
    void setDefaultApi(APISettings *apiSettings);

    /**
     * Set default API by giving name.
     * @param name API name.
     */
    void setDefaultApi(QString name);

    /**
     * Get Default API settings.
     * @return default API settings.
     */
    APISettings *getDefaultApi();

    /**
     * Save app settings
     */
    void save();

private:
    QList<APISettings *> apiSettingsList;
    APISettings *defaultApi;
};


#endif //INSTANT_TRANSLATOR_APPSETTINGS_H
