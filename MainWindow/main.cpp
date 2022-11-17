#include "Window/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window::MainWindow w;
    w.show();
    return a.exec();
}
