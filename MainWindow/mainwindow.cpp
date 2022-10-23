#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../AlgorithmsModule/algorithmsmodule.h"
#include "ListElements/CAlgorithmsListWidgetItem.h"
#include <QMessageBox>
#include <QString>

namespace Window
{

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        initializeListView();
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::on_RunAlgorithmButton_clicked()
    {
        AlgorithmsModule module;
        const auto itemPtr = ui->AlgorithmsListWidget->currentItem();
        if(itemPtr != nullptr)
            QMessageBox::about(this, "RunClicked", itemPtr->text());
    }

    void MainWindow::initializeListView() const
    {
        AlgorithmsModule module;
        ui->AlgorithmsListWidget->addItem(new AlgorithmsListItem::CAlgorithmsListWidgetItem(std::string(module.getName())));
    }

}//Window

