#include "CPainterFactory.h"
#include "BruteForce/CPainter.h"

namespace Visualization
{

    CPainterFactory::CPainterFactory(QGraphicsView* view) :
        m_view(view)
    {
    }

    PainterPtr CPainterFactory::createBruteForcePainter() const
    {
        return std::make_unique<BruteForce::CPainter>(m_view);
    }

} //Visualization
