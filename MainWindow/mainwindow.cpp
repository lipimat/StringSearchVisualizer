#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../AlgorithmsModule/algorithmsmodule.h"
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
    AlgorithmsModule module;
    QMessageBox::about(this, "RunClicked", QString::fromStdString(std::string(module.getName())));
}

