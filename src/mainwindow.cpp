#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->plainTextEdit->installEventFilter(this);
    qClipboard = QApplication::clipboard();

    QObject::connect(
            qClipboard, &QClipboard::selectionChanged,
            this, &MainWindow::clipboardSelectionChanged
    );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::clipboardSelectionChanged() {
    ui->plainTextEdit->setPlainText(qClipboard->text(QClipboard::Mode::Selection));
}
