#include <QApplication>
#include <QSettings>
#include <QList>
#include <glog/logging.h>
#include "mainwindow.h"
#include "apis/api.h"
#include "apis/googleapi.h"
#include "apis/tempapi.h"
#include "utils/apisettings.h"
#include "utils/appsettings.h"

/**
 * Create App settings.
 * @param parent Parent of an object may be viewed as the object's owner.
 * @return App settings object.
 */
AppSettings *createAppSettings(QObject *parent);

/**
 * Create APIs.
 * @return Created APIs list.
 */
QList<API *> createAPIs();

int main(int argc, char *argv[]) {
    // Logging tool.
    google::InitGoogleLogging(argv[0]);

    QApplication application(argc, argv);

    // Settings.
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("instant_translator");
    QApplication::setApplicationName("instant_translator");

    // App settings.
    AppSettings *appSettings = createAppSettings(&application);

    QList<API *> apis = createAPIs();

    // Main window.
    MainWindow mainWindow(nullptr, appSettings, apis);
    mainWindow.show();

    return application.exec();
}

AppSettings *createAppSettings(QObject *parent) {
    AppSettings *appSettings = new AppSettings();
    appSettings->setParent(parent);

    // APIs definition.
    APISettings *googleAPISettings = new APISettings(appSettings, "google", "Google Translate API");
    googleAPISettings->readSettings();
    appSettings->addApiSettings(googleAPISettings);

    APISettings *tempAPISettings = new APISettings(appSettings, "temp", "Temp API");
    tempAPISettings->readSettings();
    appSettings->addApiSettings(tempAPISettings);

    // Set default API.
    QSettings settings;
    appSettings->setDefaultApi(settings.value("default_api", "google").toString());

    return appSettings;
}

QList<API *> createAPIs() {
    QList<API *> apis;
    apis.append(new GoogleAPI());
    apis.append(new TempAPI());

    return apis;
}
