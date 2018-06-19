#ifndef INSTANT_TRANSLATOR_MAINWINDOW_H
#define INSTANT_TRANSLATOR_MAINWINDOW_H

#include <stdexcept>
#include <QMainWindow>
#include <QClipboard>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QStringList>
#include <QSettings>
#include <QMessageBox>
#include <QList>
#include <glog/logging.h>
#include "apis/api.h"
#include "apis/googleapi.h"
#include "apis/tempapi.h"
#include "dialogs/settingsdialog.h"
#include "utils/appsettings.h"
#include "utils/language.h"

namespace Ui {
    class MainWindow;
}

/**
 * Main window class.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    /**
     * Constructs an object with parent object parent.
     * @param parent Parent of an object may be viewed as the object's owner.
     * @param appSettings App settings.
     * @param apis APIs list.
     */
    explicit MainWindow(QWidget *parent, AppSettings *appSettings, const QList<API *> &apis);

    /**
     * Destructor.
     */
    ~MainWindow() override;

private slots:

    /**
     * On clipboard data is changed.
     */
    void onClipboardDataChanged();

    /**
     * On exitAction is triggered.
     */
    void on_exitAction_triggered();

    /**
     * On settingsAction is triggered.
     */
    void on_settingsAction_triggered();

    /**
     * On translateButton clicked.
     */
    void on_translateButton_clicked();

    /**
     * On swapLanguagesButton clicked.
     */
    void on_swapLanguagesButton_clicked();

private:
    /**
     * Load translation API.
     */
    void loadApi();

    /**
     * Do translation.
     */
    void doTranslation();

    /**
     * Swap languages in the combo boxes.
     */
    void swapLanguagesInComboBoxes();

    /**
     * Load languages in sourceLanguagesComboBox
     * and targetLanguagesComboBox.
     */
    void loadLanguagesInComboBoxes();

    /**
     * Run translation.
     * @param api Translation API.
     * @param inputString Text for translation.
     * @param sourceLanguage Source language code.
     * @param targetLanguage Target language code.
     * @return Translated text.
     */
    QString runTranslation(API *api,
                           const QString &inputString,
                           const QString &sourceLanguage,
                           const QString &targetLanguage);

    /**
     * Run get supported languages call.
     * @param api Translation API.
     * @return Supported languages string list.
     */
    QStringList runGetSupportedLanguages(API *api);

    /**
     * Show error box.
     * @param message Error message.
     */
    void showErrorBox(const QString &message);

    Ui::MainWindow *ui;                 // MainWindow user interface.
    QClipboard *clipboard;              // Clipboard information.
    APISettings *currentApiSettings;    // Current API settings.
    AppSettings *appSettings;           // App settings.
    QList<API *> apis;                  // Translation APIs.
    API *currentApi;                    // Current API.
    Language language;                  // Language.
};

#endif // INSTANT_TRANSLATOR_MAINWINDOW_H
