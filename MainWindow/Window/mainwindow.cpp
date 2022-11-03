#include <QMessageBox>
#include <QString>

// MainWindow includes
#include "mainwindow.h"
#include "Resources/ui_mainwindow.h"
#include "ListElements/CItem.h"

// AlgorithmsModule includes
#include "../AlgorithmsModule/SupportedAlgorithmsToolsets.h"
#include "../AlgorithmsModule/CController.h"

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

    void MainWindow::initializeListView() const
    {
        for(const auto& factory : Algorithms::toolsetFactories)
        {
            auto controllerPtr = std::make_unique<Algorithms::CController>(factory.get());
            const auto algorithmName = controllerPtr->getAlgorithmName();
            m_ui->AlgorithmsListWidget->addItem(
                        std::make_unique<ListElements::CItem>(algorithmName, controllerPtr.release()).release());
        }
    }

    void MainWindow::on_AlgorithmsListWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
    {
          if(previous != nullptr)
              previous->setBackground(QBrush(ListElements::ItemConstants::NOT_CHOSEN_ITEM_BACKGROUND_COLOR));
          if(current != nullptr)
              current->setBackground(QBrush(ListElements::ItemConstants::CHOSEN_ITEM_BACKGROUND_COLOR));
    }


    void MainWindow::on_InfoButton_clicked()
    {
        auto controllerPtr = static_cast<ListElements::CItem*>(m_ui->AlgorithmsListWidget->currentItem())->getController();
        QMessageBox::about(
                    this,
                    QString::fromStdString(controllerPtr->getAlgorithmName()),
                    QString::fromStdString(controllerPtr->getAlgorithmInfo()));
    }

} //Window

