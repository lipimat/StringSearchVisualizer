#include "CPainterFactory.h"
#include "BruteForce/CPainter.h"
#include "BoyerMoore/CPainter.h"
#include "Automaton/CPainter.h"

namespace Visualization
{

    CPainterFactory::CPainterFactory(QGraphicsView* view) :
        m_view(view)
    {
    }

    BruteForce::PainterPtr CPainterFactory::createBruteForcePainter() const
    {
        return std::make_unique<BruteForce::CPainter>(m_view);
    }

    BoyerMoore::PainterPtr CPainterFactory::createBoyerMoorePainter() const
    {
        return std::make_unique<BoyerMoore::CPainter>(m_view);
    }

    Automaton::PainterPtr CPainterFactory::createAutomatonPainter() const
    {
        return std::make_unique<Automaton::CPainter>(m_view);
    }

} // Visualization
