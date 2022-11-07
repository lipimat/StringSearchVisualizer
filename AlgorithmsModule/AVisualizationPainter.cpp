#include "AVisualizationPainter.h"

namespace Algorithms
{

    AVisualizationPainter::AVisualizationPainter(Window::IVisualizationWidget* device) :
        QPainter(device)
    {
    }

    void AVisualizationPainter::initializeVisualization()
    {
        QPainter::setPen(Qt::blue);
        QPainter::setFont(QFont("Arial", 30));
        const QRect rectangle = QRect(0, 0, 100, 50);
        QPainter::drawText(rectangle, Qt::AlignCenter, "Qt");
    }

} //Algorithms
