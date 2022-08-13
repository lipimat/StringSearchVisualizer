#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RunAlgorithmButton_clicked()
{
    QMessageBox::about(this, "RunClicked", "Hooray!");
}

