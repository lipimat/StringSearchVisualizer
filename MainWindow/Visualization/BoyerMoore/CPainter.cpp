#include "CPainter.h"

namespace Visualization
{
namespace BoyerMoore
{
    CPainter::CPainter(QGraphicsView* view) :
        ABasePainter(view)
    {
    }

    void CPainter::drawBasicScene(const TextsPair& userTexts)
    {
        ABasePainter::drawBasicScene(userTexts);
    }

    void CPainter::paint(const Algorithms::Steps::CComparison<PainterPtr>* comparisonStep)
    {
        auto color = comparisonStep->m_comparisonType == Algorithms::Steps::EComparisonType::MATCH
                ? Qt::green : Qt::red;
        if(comparisonStep->m_comparisonType == Algorithms::Steps::EComparisonType::IDLE)
        {
            clearAllHighlight();
            color = Qt::yellow;
        }

        colorRects(m_sourceRectItems, comparisonStep->m_sourceIndices, color);
        colorRects(m_patternRectItems, comparisonStep->m_patternIndices, color);
    }

    void CPainter::paint(const Algorithms::Steps::CMovePattern<PainterPtr>* movePatternStep)
    {
        clearAllHighlight();
        for(const auto& rect : m_patternRectItems)
            rect->move(movePatternStep->m_moveBy * Constants::RECT_WIDTH, 0);
    }

    void CPainter::finishScene(const Indices& sourceIndices)
    {
        ABasePainter::finishScene(sourceIndices);
    }


    void CPainter::cleanWholeScene()
    {
        ABasePainter::cleanWholeScene();
        m_view->scene()->clear();
    }

} // BoyerMoore
} // Visualization
