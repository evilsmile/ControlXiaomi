#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Hacker;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void sendFile();
    void selectFile();

private:
    Ui::MainWindow *ui;
    Hacker *hacker;
};

#endif // MAINWINDOW_H
