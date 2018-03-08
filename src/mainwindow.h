#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>
#include "utils/api.h"
#include "utils/googleapi.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void onClipboardDataChanged();
    void on_exitAction_triggered();

private:
    Ui::MainWindow *ui;
    QClipboard *clipboard;
    API *api;
};

#endif // MAINWINDOW_H
