#include "mainwindow.h"
#include "Resources/ui_mainwindow.h"

#include <QMessageBox>
#include <QString>

#include "ListElements/CItem.h"

namespace Window
{

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , m_ui(std::make_unique<Ui::MainWindow>().release())
    {
        m_ui->setupUi(this);
        initializeListView();
    }

    MainWindow::~MainWindow()
    {
        delete m_ui;
    }

    void MainWindow::on_RunAlgorithmButton_clicked()
    {
        const auto itemPtr = m_ui->AlgorithmsListWidget->currentItem();
        if(itemPtr != nullptr)
            QMessageBox::about(this, "RunClickedChange", itemPtr->text());
    }

    void MainWindow::initializeListView() const
    {
        m_ui->AlgorithmsListWidget->addItem(new ListElements::CItem(std::string("Brute Force")));
        m_ui->AlgorithmsListWidget->addItem(new ListElements::CItem(std::string("alg2")));
    }

    void MainWindow::on_AlgorithmsListWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
    {
          if(previous != nullptr)
              previous->setBackground(QBrush(ListElements::ItemConstants::NOT_CHOSEN_ITEM_BACKGROUND_COLOR));
          if(current != nullptr)
              current->setBackground(QBrush(ListElements::ItemConstants::CHOSEN_ITEM_BACKGROUND_COLOR));
    }

}//Window

