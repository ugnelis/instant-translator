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

    api = new GoogleAPI();
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

    QString outputString = QString::fromStdString(api->translate(inputString.toStdString()));
    ui->outpuPlainTextEdit->setPlainText(outputString);
}

void MainWindow::on_exitAction_triggered() {
    this->close();
}
