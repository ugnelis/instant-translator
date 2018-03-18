#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    clipboard = QApplication::clipboard();

    QObject::connect(
            clipboard, &QClipboard::dataChanged,
            this, &MainWindow::onClipboardDataChanged
    );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onClipboardDataChanged() {
    // Bring app to front.
    this->setWindowState(Qt::WindowActive);

    QString inputString = clipboard->text(QClipboard::Mode::Clipboard);
    ui->inputPlainTextEdit->setPlainText(inputString);

    // Translate text in different thread.
    QFutureWatcher<QString> *futureWatcher = new QFutureWatcher<QString>(this);
    QFuture<QString> future = QtConcurrent::run(this, &MainWindow::runTranslation, inputString);

    // Output translated text
    connect(futureWatcher, &QFutureWatcher<QString>::finished,
            [=]() { this->ui->outpuPlainTextEdit->setPlainText(futureWatcher->result()); });

    futureWatcher->setFuture(future);
}

QString MainWindow::runTranslation(const QString &inputString) {
    GoogleAPI api;
    QString outputString = api.translate(inputString);
    return outputString;
}

void MainWindow::on_exitAction_triggered() {
    this->close();
}
