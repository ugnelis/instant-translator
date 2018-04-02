#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    clipboard = QApplication::clipboard();

    api = new GoogleAPI();

    // Load API supported languages to the combo boxes.
    QStringList languages = api->getSupportedLanguages();

    ui->sourceLanguagesComboBox->addItems(languages);
    ui->targetLanguagesComboBox->addItems(languages);

    connect(
            clipboard,
            &QClipboard::dataChanged,
            this,
            &MainWindow::onClipboardDataChanged
    );
}

MainWindow::~MainWindow() {
    delete ui;
    delete api;
}

void MainWindow::onClipboardDataChanged() {
    // Bring app to front.
    this->setWindowState(Qt::WindowActive);

    QString inputString = clipboard->text(QClipboard::Mode::Clipboard);
    ui->inputPlainTextEdit->setPlainText(inputString);

    // Translate text in different thread.
    QFutureWatcher<QString> *futureWatcher = new QFutureWatcher<QString>(this);
    QString sourceLanguage = "de";
    QString targetLanguage = "en";
    QFuture<QString> future = QtConcurrent::run(
            this,
            &MainWindow::runTranslation,
            api,
            inputString,
            sourceLanguage,
            targetLanguage
    );

    // Output translated text
    connect(
            futureWatcher,
            &QFutureWatcher<QString>::finished,
            [=]() { this->ui->outpuPlainTextEdit->setPlainText(futureWatcher->result()); }
    );

    futureWatcher->setFuture(future);
}

QString MainWindow::runTranslation(API *api,
                                   const QString &inputString,
                                   const QString &sourceLanguage,
                                   const QString &targetLanguage) {
    if (api == NULL) {
        return "";
    }

    QString outputString = api->translate(inputString, sourceLanguage, targetLanguage);
    return outputString;
}

void MainWindow::on_exitAction_triggered() {
    this->close();
}
