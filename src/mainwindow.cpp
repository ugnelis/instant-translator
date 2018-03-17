#include <QDebug>
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

    QFuture<void> future = QtConcurrent::run(this, &MainWindow::runTranslation, inputString);
//    future.waitForFinished();
}

void MainWindow::runTranslation(QString inputString) {
    GoogleAPI api;
    QString outputString = api.translate(inputString);
    QObject::connect(
            clipboard, &QClipboard::dataChanged,
            this, &MainWindow::onClipboardDataChanged
    );
//    ui->outpuPlainTextEdit->setPlainText(outputString);
}

void MainWindow::on_exitAction_triggered() {
    this->close();
}
