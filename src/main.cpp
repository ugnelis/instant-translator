#include <QApplication>
#include <QSettings>
#include <glog/logging.h>
#include "mainwindow.h"
#include "utils/apisettings.h"
#include "utils/appsettings.h"

int main(int argc, char *argv[]) {
    // Logging tool.
    google::InitGoogleLogging(argv[0]);

    QApplication application(argc, argv);

    // Settings.
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("instant_translator");
    QApplication::setApplicationName("instant_translator");

    // App settings.
    AppSettings *appSettings = new AppSettings();
    appSettings->setParent(&application);

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

    // Main window.
    MainWindow mainWindow(nullptr, appSettings);
    mainWindow.show();

    return application.exec();
}
