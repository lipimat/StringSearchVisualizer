#include <QMessageBox>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsRectItem>

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
        const auto controllerPtr = static_cast<ListElements::CItem*>(m_ui->AlgorithmsListWidget->currentItem())->getController();
        QMessageBox::about(
                    this,
                    QString::fromStdString(controllerPtr->getAlgorithmName()),
                    QString::fromStdString(controllerPtr->getAlgorithmInfo()));
    }

    void MainWindow::on_StartButton_clicked()
    {
        const auto sourceText = m_ui->SourceLineEdit->text().toStdString();
        const auto patternText = m_ui->PatternLineEdit->text().toStdString();
        if(sourceText.empty() || patternText.empty())
        {
            QMessageBox::critical(this, "Error", "Fill both forms to start simulation!");
            return;
        }

        initializeLayoutSimulation();
        const auto controllerPtr = static_cast<ListElements::CItem*>(m_ui->AlgorithmsListWidget->currentItem())->getController();
        controllerPtr->initializeScene();
        QGraphicsScene* scene = new QGraphicsScene();
        QGraphicsRectItem* item1 = new QGraphicsRectItem(0,0,100,100);
        QGraphicsTextItem* tItem1 = new QGraphicsTextItem("cos");
        QGraphicsRectItem* item2 = new QGraphicsRectItem(0,100,100,100);
        QGraphicsRectItem* item3 = new QGraphicsRectItem(100,0,100,100);
        QGraphicsRectItem* item4 = new QGraphicsRectItem(100,100,100,100);


        item1->setBrush(QBrush(Qt::red));
        item2->setBrush(QBrush(Qt::green));
        item3->setBrush(QBrush(Qt::blue));
        item4->setBrush(QBrush(Qt::yellow));

        scene->addItem(item1);
        scene->addItem(tItem1);
        scene->addItem(item2);
        scene->addItem(item3);
        scene->addItem(item4);
        m_ui->GraphicsView->setScene(scene);
    }


    void MainWindow::on_StopButton_clicked()
    {
        initializeLayoutNoSimulation();
        m_ui->GraphicsView->scene()->clear();
    }

} //Window

