#include "Window/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window::MainWindow w;
    w.show();
    return a.exec();
}
