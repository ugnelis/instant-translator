#include <QApplication>
#include <QSettings>
#include <glog/logging.h>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    // Logging tool.
    google::InitGoogleLogging(argv[0]);

    QApplication application(argc, argv);

    // Settings.
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("instant_translator");
    QApplication::setApplicationName("instant_translator");

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
