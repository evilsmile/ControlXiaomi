#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesender.h"
#include "hacker.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    hacker(new Hacker(this))
{
    ui->setupUi(this);
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendFile()));
    connect(ui->fileSelectButton, SIGNAL(clicked()), this, SLOT(selectFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete hacker;
}

void MainWindow::sendFile()
{
    hacker->sendFile(ui->file_path_edit->displayText());
}

void MainWindow::selectFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select File", "/home/evilsmile");
    ui->file_path_edit->setText(filePath);
}
