#pragma once

#include "../../AlgorithmsModule/IPainterFactory.h"
#include "Window/ListElements/CItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QListWidgetItem;

namespace Window
{

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:

        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:

        void on_AlgorithmsListWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*);

        void on_InfoButton_clicked();

        void on_StopButton_clicked();

        void on_NextStepButton_clicked();

        void on_AutoSimStartButton_clicked();

        void on_ManualSimStartButton_clicked();

        void on_SimType_stateChanged(int arg1);

    private:

        void initializeLayoutNoSimulation() const;

        void initializeLayoutSimulation() const;

        void initializeListView() const;

        Ui::MainWindow* m_ui;
        // i don't know how to stop it so I need member :(
        std::unique_ptr<QTimer> m_timer;

        ListElements::CItem* m_currentSimulationItem;

        Visualization::PainterFactoryPtr m_painterFactory;
    };

} // Window
