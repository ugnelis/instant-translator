#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QStringList>
#include "utils/api.h"
#include "utils/googleapi.h"

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
     */
    explicit MainWindow(QWidget *parent = nullptr);

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
     * On exitAction is changed.
     */
    void on_exitAction_triggered();

    /**
     * On translateButton clicked.
     */
    void on_translateButton_clicked();

private:
    /**
     * Do translation.
     */
    void doTranslation();

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

    Ui::MainWindow *ui;     // MainWindow user interface.
    QClipboard *clipboard;  // Clipboard information.
    API *api;               // Translation API.
};

#endif // MAINWINDOW_H
