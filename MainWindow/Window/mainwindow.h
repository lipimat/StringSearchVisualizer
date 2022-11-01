#pragma once

#include <QMainWindow>

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

        void on_RunAlgorithmButton_clicked();
        void on_AlgorithmsListWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*);

    private:

        void initializeListView() const;

        Ui::MainWindow* m_ui;
    };

}//Window
