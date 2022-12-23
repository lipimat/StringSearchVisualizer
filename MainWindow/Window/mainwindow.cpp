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
          m_currentSimulationItem(nullptr),
          m_timer(std::make_unique<QTimer>(this))
    {
        m_ui->setupUi(this);

        const auto supportedAlphabetLabel =
                "Supported alphabet: " + std::string(Algorithms::SUPPORTED_ALPHABET);
        m_ui->AlphabetLabel->setText(QString::fromStdString(supportedAlphabetLabel));
        m_painterFactory = std::make_unique<Visualization::CPainterFactory>(m_ui->GraphicsView);
        initializeLayoutNoSimulation();
        initializeListView();
        connect(m_timer.get(), &QTimer::timeout, this, &MainWindow::on_NextStepButton_clicked);
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
        m_ui->SimType->setDisabled(false);
        m_ui->SimStepTime->setDisabled(false);
        if(m_ui->SimType->isChecked())
        {
            m_ui->AutoSimStartButton->show();
            m_ui->SimStepTime->show();
            m_ui->TimerStartVal->show();
            m_ui->TimerEndVal->show();
            m_ui->ManualSimStartButton->hide();
            m_ui->NextStepButton->hide();
            m_ui->StopButton->hide();
        }
        else
        {
            m_ui->AutoSimStartButton->hide();
            m_ui->SimStepTime->hide();
            m_ui->TimerStartVal->hide();
            m_ui->TimerEndVal->hide();
            m_ui->ManualSimStartButton->show();
            m_ui->NextStepButton->hide();
            m_ui->StopButton->hide();
        }
    }

    void MainWindow::initializeLayoutSimulation() const
    {
        m_ui->AlgorithmsListWidget->blockSignals(true);
        m_ui->SourceLineEdit->setReadOnly(true);
        m_ui->PatternLineEdit->setReadOnly(true);
        m_ui->SimType->setDisabled(true);
        m_ui->SimStepTime->setDisabled(true);
        m_ui->ManualSimStartButton->hide();
        m_ui->AutoSimStartButton->hide();
        m_ui->StopButton->show();
        if(!m_ui->SimType->isChecked())
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

    void MainWindow::on_ManualSimStartButton_clicked()
    {
        const auto& sourceText = m_ui->SourceLineEdit->text().toStdString();
        const auto& patternText = m_ui->PatternLineEdit->text().toStdString();
        try {
            assert(m_currentSimulationItem != nullptr);
            m_currentSimulationItem->initializeVisualization({sourceText, patternText});
        } catch (std::runtime_error e) {
            QMessageBox::critical(this, "Input!", e.what());
            return;
        }

        initializeLayoutSimulation();
    }


    void MainWindow::on_AutoSimStartButton_clicked()
    {
        on_ManualSimStartButton_clicked();
        m_timer->start(m_ui->SimStepTime->value() * 10); //convert to ms
    }


    void MainWindow::on_StopButton_clicked()
    {
        //UGLY TOO
        if(m_timer->isActive())
            m_timer->stop();
        initializeLayoutNoSimulation();
        m_currentSimulationItem->clearVisualization();
    }


    void MainWindow::on_NextStepButton_clicked()
    {
        assert(m_currentSimulationItem != nullptr);
        const auto cannotPerformNextStep = !m_currentSimulationItem->nextStep();
        if(cannotPerformNextStep)
        {
            m_ui->NextStepButton->hide();
            if(m_timer->isActive())
                m_timer->stop(); //UGLY!
        }
    }


    void MainWindow::on_SimType_stateChanged(int arg1)
    {
        // turned on
        if(arg1 == 2)
        {
            m_ui->ManualSimStartButton->hide();
            m_ui->AutoSimStartButton->show();
            m_ui->SimStepTime->show();
            m_ui->TimerStartVal->show();
            m_ui->TimerEndVal->show();
        }
        else
        {
            m_ui->ManualSimStartButton->show();
            m_ui->AutoSimStartButton->hide();
            m_ui->SimStepTime->hide();
            m_ui->TimerStartVal->hide();
            m_ui->TimerEndVal->hide();
        }
    }

} // Window

