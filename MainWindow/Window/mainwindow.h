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
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow() = default;

    private slots:
        void on_RunAlgorithmButton_clicked();
        void on_AlgorithmsListWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*);

    private:

        void initializeListView() const;

        std::unique_ptr<Ui::MainWindow> ui;
    };

}//Window
