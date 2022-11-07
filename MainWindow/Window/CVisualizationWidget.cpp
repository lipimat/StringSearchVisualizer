#include "CVisualizationWidget.h"
#include "../AlgorithmsModule/BruteForce/CVisualizationPainter.h"

namespace Window
{

    CVisualizationWidget::CVisualizationWidget(QWidget* parent) :
        QWidget(parent)
    {
    }

    void CVisualizationWidget::paintEvent(QPaintEvent*)
    {
        Algorithms::BruteForce::CVisualizationPainter x(this);
        x.initializeVisualization();
        //if(m_paintingFunction)
        //    m_paintingFunction();
    }

    void CVisualizationWidget::updateWithGivenFunction(std::function<void()> paintingFunction)
    {
        m_paintingFunction = paintingFunction;
        this->update();
    }

} //Window
