// MainWindow includes
#include "mainwindow.h"
#include "Resources/ui_mainwindow.h"
#include "ListElements/CItem.h"
#include "../Visualization/CPainterFactory.h"

// AlgorithmsModule includes
#include "../../AlgorithmsModule/SupportedAlgorithmsAlphabet.h"
#include "../../AlgorithmsModule/SupportedAlgorithmsControllers.h"

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
        for(const auto& factoryPtr : Algorithms::SUPPORTED_CONTROLLERS)
        {
            m_ui->AlgorithmsListWidget->addItem(
                        std::make_unique<ListElements::CItem>(factoryPtr->createController(m_painterFactory)).release());
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
        QMessageBox::about(this, m_currentSimulationItem->getName(), m_currentSimulationItem->getInfo());
    }

    void MainWindow::on_StartButton_clicked()
    {
        //move this into controller and throw exceptions
        const auto& sourceText = m_ui->SourceLineEdit->text().toStdString();
        const auto& patternText = m_ui->PatternLineEdit->text().toStdString();
        try {
            assert(m_currentSimulationItem != nullptr);
            m_currentSimulationItem->initializeVisualization({sourceText, patternText});
            initializeLayoutSimulation();
        } catch (std::runtime_error e) {
            QMessageBox::critical(this, "Input!", e.what());
        }
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

} // Window

