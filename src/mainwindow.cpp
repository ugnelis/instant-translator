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
    ui->plainTextEdit->setPlainText(clipboard->text(QClipboard::Mode::Clipboard));

    // Bring app to front.
    this->setWindowState(Qt::WindowActive);
}

void MainWindow::on_exitAction_triggered() {
    this->close();
}
