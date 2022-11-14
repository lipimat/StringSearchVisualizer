#include <QMessageBox>

// MainWindow includes
#include "mainwindow.h"
#include "Resources/ui_mainwindow.h"
#include "ListElements/CItem.h"
#include "Visualization/CPainter.h"

// AlgorithmsModule includes
#include "../AlgorithmsModule/SupportedAlgorithmsToolsets.h"
#include "../AlgorithmsModule/CController.h"

namespace Window
{

    namespace
    {
        const auto castItem = [](QListWidgetItem* const item)
        {
            ListElements::CItem* ret = nullptr;
            if(item != nullptr && (ret = dynamic_cast<ListElements::CItem*>(item)))
                assert(ret);
            return ret;
        };
    } //anonymous

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          m_ui(std::make_unique<Ui::MainWindow>().release())
    {
        m_ui->setupUi(this);
        m_painter = std::make_shared<Visualization::CPainter>(m_ui->GraphicsView);
        initializeLayoutNoSimulation();
        initializeListView();
    }

    MainWindow::~MainWindow()
    {
        delete m_ui;
    }

    void MainWindow::initializeLayoutNoSimulation() const
    {
        m_ui->SourceLineEdit->setReadOnly(false);
        m_ui->PatternLineEdit->setReadOnly(false);
        m_ui->StartButton->show();
        m_ui->StopButton->hide();
        m_ui->NextStepButton->hide();
    }

    void MainWindow::initializeLayoutSimulation() const
    {
        m_ui->SourceLineEdit->setReadOnly(true);
        m_ui->PatternLineEdit->setReadOnly(true);
        m_ui->StartButton->hide();
        m_ui->StopButton->show();
        m_ui->NextStepButton->show();
    }

    void MainWindow::initializeListView() const
    {
        for(const auto& factoryPtr : Algorithms::SUPPORTED_TOOLSETS)
        {
            m_ui->AlgorithmsListWidget->addItem(
                        std::make_unique<ListElements::CItem>(
                            std::make_unique<Algorithms::CController>(factoryPtr, m_painter))
                        .release());
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
        const auto& itemPtr = castItem(m_ui->AlgorithmsListWidget->currentItem());
        QMessageBox::about(this,itemPtr->getName(),itemPtr->getInfo());
    }

    void MainWindow::on_StartButton_clicked()
    {
        const auto& sourceText = m_ui->SourceLineEdit->text().toStdString();
        const auto& patternText = m_ui->PatternLineEdit->text().toStdString();
        if(sourceText.empty() || patternText.empty())
        {
            QMessageBox::critical(this, "Error", "Fill both forms to start simulation!");
            return;
        }

        initializeLayoutSimulation();
        const auto& itemPtr = castItem(m_ui->AlgorithmsListWidget->currentItem());
        itemPtr->initializeVisualization({sourceText, patternText});
    }


    void MainWindow::on_StopButton_clicked()
    {
        initializeLayoutNoSimulation();
        const auto& itemPtr = castItem(m_ui->AlgorithmsListWidget->currentItem());
        itemPtr->clearVisualization();
    }


    void MainWindow::on_NextStepButton_clicked()
    {
        const auto& itemPtr = castItem(m_ui->AlgorithmsListWidget->currentItem());
        const auto cannotPerformNextStep = !itemPtr->nextStep();
        if(cannotPerformNextStep)
            QMessageBox::about(this,itemPtr->getName(),"Finished!");
    }

} //Window

