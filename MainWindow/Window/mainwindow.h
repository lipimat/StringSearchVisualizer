#pragma once

#include "../../AlgorithmsModule/IPainterFactory.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QListWidgetItem;

namespace Window
{

    using PainterPtr = Visualization::PainterPtr;

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:

        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:

        void on_AlgorithmsListWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*);

        void on_InfoButton_clicked();

        void on_StartButton_clicked();

        void on_StopButton_clicked();

        void on_NextStepButton_clicked();

    private:

        void initializeLayoutNoSimulation() const;

        void initializeLayoutSimulation() const;

        void initializeListView() const;

        Ui::MainWindow* m_ui;

        Visualization::PainterFactoryPtr m_painterFactory;
    };

}//Window
