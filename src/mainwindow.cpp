#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    clipboard = QApplication::clipboard();

    connect(
            clipboard,
            &QClipboard::dataChanged,
            this,
            &MainWindow::onClipboardDataChanged
    );

    // Set Google Translator API.
    api = new GoogleAPI(this);

    // Load supported languages in the combo boxes.
    loadLanguagesInComboBoxes();
}

MainWindow::~MainWindow() {
    // Save used translation languages.
    QSettings settings;
    QString sourceLanguage = language.getCode(ui->sourceLanguagesComboBox->currentText());
    QString targetLanguage = language.getCode(ui->targetLanguagesComboBox->currentText());
    settings.setValue("source", sourceLanguage);
    settings.setValue("target", targetLanguage);

    delete ui;
    delete api;
}

void MainWindow::onClipboardDataChanged() {
    // Bring app to front.
    this->setWindowState(Qt::WindowActive);

    QString inputString = clipboard->text(QClipboard::Mode::Clipboard);
    ui->inputPlainTextEdit->setPlainText(inputString);

    // Perform translation.
    doTranslation();
}

void MainWindow::doTranslation() {
    QString inputString = ui->inputPlainTextEdit->toPlainText();

    // Translate text in different thread.
    QFutureWatcher<QString> *futureWatcher = new QFutureWatcher<QString>(this);

    QString sourceLanguage = language.getCode(ui->sourceLanguagesComboBox->currentText());
    QString targetLanguage = language.getCode(ui->targetLanguagesComboBox->currentText());
    QFuture<QString> future = QtConcurrent::run(
            this,
            &MainWindow::runTranslation,
            api,
            inputString,
            sourceLanguage,
            targetLanguage
    );

    // Output translated text.
    connect(
            futureWatcher,
            &QFutureWatcher<QString>::finished,
            [=]() { this->ui->outpuPlainTextEdit->setPlainText(futureWatcher->result()); }
    );

    futureWatcher->setFuture(future);
}

void MainWindow::swapLanguagesInComboBoxes() {
    int sourceLanguagesComboBoxIndex = ui->sourceLanguagesComboBox->currentIndex();
    int targetLanguagesComboBoxIndex = ui->targetLanguagesComboBox->currentIndex();

    ui->sourceLanguagesComboBox->setCurrentIndex(targetLanguagesComboBoxIndex);
    ui->targetLanguagesComboBox->setCurrentIndex(sourceLanguagesComboBoxIndex);
}

void MainWindow::loadLanguagesInComboBoxes() {
    // Get API supported languages.
    QFutureWatcher<QStringList> *futureWatcher = new QFutureWatcher<QStringList>(this);
    QFuture<QStringList> future = QtConcurrent::run(
            this,
            &MainWindow::runGetSupportedLanguages,
            api
    );

    // Load API supported languages to the combo boxes.
    connect(
            futureWatcher,
            &QFutureWatcher<QStringList>::finished,
            [=]() {
                QStringList languageCodeList = futureWatcher->result();
                QStringList languageNameList = language.getLanguages(languageCodeList);
                ui->sourceLanguagesComboBox->addItems(languageNameList);
                ui->targetLanguagesComboBox->addItems(languageNameList);

                // Load saved translation languages.
                QSettings settings;
                QString sourceLanguage = settings.value("source", "de").toString();
                QString targetLanguage = settings.value("target", "en").toString();

                // Set source language.
                int sourceLanguageIndex = languageCodeList.indexOf(sourceLanguage);
                if (sourceLanguageIndex != -1) {
                    ui->sourceLanguagesComboBox->setCurrentIndex(sourceLanguageIndex);
                }

                // Set target language.
                int targetLanguageIndex = languageCodeList.indexOf(targetLanguage);
                if (targetLanguageIndex != -1) {
                    ui->targetLanguagesComboBox->setCurrentIndex(targetLanguageIndex);
                }
            }
    );
    futureWatcher->setFuture(future);
}

QString MainWindow::runTranslation(API *api,
                                   const QString &inputString,
                                   const QString &sourceLanguage,
                                   const QString &targetLanguage) {
    if (api == nullptr) {
        showErrorBox("Text cannot be translated. API is not set.");
        return QString();
    }

    QString outputString;
    try {
        outputString = api->translate(inputString, sourceLanguage, targetLanguage);
    } catch (const std::invalid_argument &e) {
        showErrorBox(e.what());
    }

    return outputString;
}

QStringList MainWindow::runGetSupportedLanguages(API *api) {
    if (api == nullptr) {
        showErrorBox("Languages list cannot be received. API is not set.");
        return QStringList();
    }

    QStringList supportedLanguages;
    try {
        supportedLanguages = api->getSupportedLanguages();
    } catch (const std::invalid_argument &e) {
        showErrorBox(e.what());
    }

    return supportedLanguages;
}

void MainWindow::showErrorBox(const QString &message) {
    DLOG(INFO) << message.toStdString();
    QMessageBox messageBox;
    messageBox.setText(message);
    messageBox.setIcon(QMessageBox::Warning);
    messageBox.exec();
}

void MainWindow::on_exitAction_triggered() {
    this->close();
}

void MainWindow::on_translateButton_clicked() {
    // Perform translation.
    doTranslation();
}

void MainWindow::on_swapLanguagesButton_clicked() {
    // Swap languages in the combo boxes.
    swapLanguagesInComboBoxes();
}