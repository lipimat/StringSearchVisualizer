// MainWindow includes
#include "mainwindow.h"
#include "Resources/ui_mainwindow.h"
#include "ListElements/CItem.h"
#include "../Visualization/CPainterFactory.h"

// AlgorithmsModule includes
#include "../../AlgorithmsModule/SupportedAlgorithmsToolsets.h"
#include "../../AlgorithmsModule/CController.h"

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
          m_ui(std::make_unique<Ui::MainWindow>().release()),
          m_currentSimulationItem(nullptr)
    {
        m_ui->setupUi(this);

        const auto supportedAlphabetLabel =
                "Supported alphabet: " + std::string(Algorithms::SUPPORTED_ALPHABET);
        m_ui->AlphabetLabel->setText(QString::fromStdString(supportedAlphabetLabel));

        m_painterFactory = std::make_unique<Visualization::CPainterFactory>(m_ui->GraphicsView);
        initializeLayoutNoSimulation();
        initializeListView();
    }

    MainWindow::~MainWindow()
    {
        delete m_ui;
    }

    void MainWindow::initializeLayoutNoSimulation() const
    {
        m_ui->AlgorithmsListWidget->blockSignals(false);
        m_ui->SourceLineEdit->setReadOnly(false);
        m_ui->PatternLineEdit->setReadOnly(false);
        m_ui->StartButton->show();
        m_ui->StopButton->hide();
        m_ui->NextStepButton->hide();
    }

    void MainWindow::initializeLayoutSimulation() const
    {
        m_ui->AlgorithmsListWidget->blockSignals(true);
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
                            std::make_unique<Algorithms::CController>(factoryPtr, m_painterFactory))
                        .release());
        }
    }

    void MainWindow::on_AlgorithmsListWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
    {
          if(previous != nullptr)
              previous->setBackground(QBrush(ListElements::ItemConstants::NOT_CHOSEN_ITEM_BACKGROUND_COLOR));
          if(current != nullptr)
          {
              current->setBackground(QBrush(ListElements::ItemConstants::CHOSEN_ITEM_BACKGROUND_COLOR));
              m_currentSimulationItem = castItem(current);
          }
    }


    void MainWindow::on_InfoButton_clicked()
    {
        QMessageBox::about(this,m_currentSimulationItem->getName(),m_currentSimulationItem->getInfo());
    }

    void MainWindow::on_StartButton_clicked()
    {
        const auto& sourceText = m_ui->SourceLineEdit->text().toStdString();
        const auto& patternText = m_ui->PatternLineEdit->text().toStdString();
        if(sourceText.empty() || patternText.empty())
        {
            QMessageBox::critical(this, "Input!", "Fill both forms to start simulation!");
            return;
        }
        //check if our texts fit into supported alphabet
        const auto alphabetRegex = "^[" + std::string(Algorithms::SUPPORTED_ALPHABET) + "]+$";
        QRegExp checker(QString::fromStdString(alphabetRegex));
        if(checker.indexIn(QString::fromStdString(sourceText)) ||
                checker.indexIn(QString::fromStdString(patternText)))
        {
            QMessageBox::critical(this, "Input!", "Input texts need to contain only supported alphabet letters!");
            return;
        }

        initializeLayoutSimulation();
        assert(m_currentSimulationItem != nullptr);
        m_currentSimulationItem->initializeVisualization({sourceText, patternText});
    }


    void MainWindow::on_StopButton_clicked()
    {
        initializeLayoutNoSimulation();
        m_currentSimulationItem->clearVisualization();
    }


    void MainWindow::on_NextStepButton_clicked()
    {
        assert(m_currentSimulationItem != nullptr);
        const auto cannotPerformNextStep = !m_currentSimulationItem->nextStep();
        if(cannotPerformNextStep)
            m_ui->NextStepButton->hide();
    }

} //Window

