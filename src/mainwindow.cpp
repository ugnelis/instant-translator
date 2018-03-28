#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <functional>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    clipboard = QApplication::clipboard();

    api = new GoogleAPI();

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
    QFuture<QString> future = QtConcurrent::run(this, &MainWindow::runTranslation, inputString, api);

    // Output translated text
    connect(
            futureWatcher,
            &QFutureWatcher<QString>::finished,
            [=]() { this->ui->outpuPlainTextEdit->setPlainText(futureWatcher->result()); }
    );

    futureWatcher->setFuture(future);
}

QString MainWindow::runTranslation(const QString &inputString, API *api) {
    if (api == NULL) {
        return "";
    }

    QString outputString = api->translate(inputString);
    return outputString;
}

void MainWindow::on_exitAction_triggered() {
    this->close();
}
