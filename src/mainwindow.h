#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>

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
};

#endif // MAINWINDOW_H
