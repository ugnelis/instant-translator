#include <QApplication>
#include <QSettings>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    // Settings.
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("instant_translator");
    QApplication::setApplicationName("instant_translator");

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
