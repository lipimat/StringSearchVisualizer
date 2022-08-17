#include "mainwindow.h"
#include "Resources/ui_mainwindow.h"

#include <QMessageBox>
#include <QString>

#include "../AlgorithmsModule/algorithmsmodule.h"
#include "ListElements/CAlgorithmsListWidgetItem.h"

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
        ui->AlgorithmsListWidget->addItem(new ListElements::CAlgorithmsListWidgetItem(std::string(module.getName())));
        ui->AlgorithmsListWidget->addItem(new ListElements::CAlgorithmsListWidgetItem(std::string("alg2")));
    }

    void MainWindow::on_AlgorithmsListWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
    {
          if(previous != nullptr)
              previous->setBackground(QBrush(ListElements::ItemConstants::NOT_CHOSEN_ITEM_BACKGROUND_COLOR));
          if(current != nullptr)
              current->setBackground(QBrush(ListElements::ItemConstants::CHOSEN_ITEM_BACKGROUND_COLOR));
    }

}//Window

