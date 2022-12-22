#include "CPainter.h"

namespace Visualization
{
namespace Automaton
{
    CPainter::CPainter(QGraphicsView* view) :
        ABasePainter(view)
    {
    }

    void CPainter::drawBasicScene(const TextsPair& userTexts)
    {
        ABasePainter::drawBasicScene(userTexts);
        for(const auto& sourceRect : m_sourceRectItems)
            sourceRect->hide(); //we only need pattern to build automat
        for(const auto& patternRect : m_patternRectItems)
            patternRect->move(0, -250);

        m_drawBackwardsArrowUp = true;
    }

    void CPainter::paint(const Algorithms::Steps::CDrawAutomatonNode<PainterPtr>* drawNodeStep)
    {
        using namespace Constants;
        const auto& scene = m_view->scene();
        clearAllHighlight();
        if(drawNodeStep->m_stateNumber > 0)
            m_patternRectItems[drawNodeStep->m_stateNumber-1]->setBrush(QBrush(Constants::ELLIPSE_HIGHLIGHT_COLOR));
        const auto& ellipseItem = std::make_shared<CEllipseItem>(calculateRectForNode(drawNodeStep->m_stateNumber),
                                                                 std::to_string(drawNodeStep->m_stateNumber));

        scene->addItem(ellipseItem.get());
        scene->addItem(ellipseItem->getText().get());
        m_automaton.push_back(ellipseItem);
        for(const auto& nodeRelation : drawNodeStep->m_nodeRelations)
        {
            const auto& targetStateNr = nodeRelation.first;
            const auto& vertexLabel = nodeRelation.second;
            QPainterPath arrow;
            // arrow to the right
            if(targetStateNr == drawNodeStep->m_stateNumber + 1)
                arrow = createRightArrow(drawNodeStep->m_stateNumber, targetStateNr, vertexLabel);
            // arrow to myself
            else if(targetStateNr == drawNodeStep->m_stateNumber)
                arrow = createSelfArrow(drawNodeStep->m_stateNumber, vertexLabel);
            else
                arrow = createBackwardsArrow(drawNodeStep->m_stateNumber, targetStateNr, vertexLabel);

            scene->addPath(arrow);
        }
    }

    void CPainter::paint(const Algorithms::Steps::CStartAutomaton<PainterPtr>* startAutomatonStep)
    {
        for(const auto& sourceRect : m_sourceRectItems)
        {
            sourceRect->move(0, -150);
            sourceRect->show(); //we only need source to run automat
        }
        for(const auto& patternRect : m_patternRectItems)
            patternRect->hide();

        m_automaton[0]->setBrush(QBrush(Constants::ELLIPSE_HIGHLIGHT_COLOR));
    }

    void CPainter::paint(const Algorithms::Steps::CStateChangedAutomaton<PainterPtr>* stateChangedAutomatonStep)
    {
        clearAllHighlight();
        m_automaton[stateChangedAutomatonStep->m_stateNr]->setBrush(QBrush(Constants::ELLIPSE_HIGHLIGHT_COLOR));
        for(const auto& idx : stateChangedAutomatonStep->m_sourceIndices)
            m_sourceRectItems[idx]->setBrush(QBrush(Constants::ELLIPSE_HIGHLIGHT_COLOR)); //highligh them both with the same color
    }

    void CPainter::finishScene(const Indices& sourceIndices)
    {
        clearAllHighlight();
        ABasePainter::finishScene(sourceIndices);
    }

    void CPainter::clearAllHighlight()
    {
        for(const auto& node : m_automaton)
            node->setBrush(QBrush(Constants::ELLIPSE_INITIAL_COLOR));
        ABasePainter::clearAllHighlight();
    }

    QPainterPath CPainter::createSelfArrow(const int state, const char label)
    {
         const auto& stateRect = calculateRectForNode(state);

         const QPointF start(stateRect.x() + stateRect.width()/2 + 10, stateRect.y());
         const QPointF rightBend(stateRect.x() + stateRect.width()/2 + 30, stateRect.y() - 30);
         const QPointF middlePoint(stateRect.x() + stateRect.width()/2, stateRect.y() - 50);
         const QPointF leftBend(stateRect.x() + stateRect.width()/2 - 30, stateRect.y() - 30);
         const QPointF stop(stateRect.x() + stateRect.width()/2 - 10, stateRect.y());
         const QPointF textPoint(middlePoint.x() - 8, middlePoint.y() - 5);

         QPainterPath path;
         path.moveTo(start);
         path.cubicTo(start, rightBend, middlePoint);
         path.cubicTo(middlePoint, leftBend, stop);
         //create arrow nose
         path.lineTo(stop.x(), stop.y() - 10);
         path.lineTo(stop);
         path.lineTo(stop.x() - 10, stop.y());

         //add label
         path.addText(textPoint, Constants::SMALLER_TEXT_FONT, QString(label));

         return path;
    }

    QPainterPath CPainter::createRightArrow(const int fromState, const int toState, const char label)
    {
        const auto& fromRect = calculateRectForNode(fromState);
        const auto& toRect = calculateRectForNode(toState);

        const QPointF start(fromRect.x() + fromRect.width(), fromRect.y() + fromRect.height()/2);
        const QPointF stop(toRect.x(), toRect.y() + toRect.height()/2);
        const QPointF textPoint(start.x(), start.y() - 10);

        QPainterPath path;
        path.moveTo(start);
        path.lineTo(stop);
        //create arrow nose
        path.lineTo(stop.x() - 5, stop.y() - 5);
        path.lineTo(stop);
        path.lineTo(stop.x() - 5, stop.y() + 5);

        //add label
        path.addText(textPoint, Constants::SMALLER_TEXT_FONT, QString(label));

        return path;
    }

    QPainterPath CPainter::createBackwardsArrow(const int fromState, const int toState, const char label)
    {
        const auto& fromRect = calculateRectForNode(fromState);
        const auto& toRect = calculateRectForNode(toState);
        const int bezierBend = (fromRect.x() - toRect.x())/2;

        QPointF start;
        QPointF bendPoint;
        QPointF stop;
        QPointF textPoint;
        if(m_drawBackwardsArrowUp)
        {
            double test = 0.5;
            start = QPointF(fromRect.x() + fromRect.width()/2, fromRect.y());
            stop =  QPointF(toRect.x() + toRect.width()/2, toRect.y());
            bendPoint = QPointF((fromRect.x() + toRect.x())/2 + 20, fromRect.y() - bezierBend);
            textPoint = QPointF(bendPoint.x() + 20, 0.25*(start.y()+2*bendPoint.y()+stop.y()));
        }
        else
        {
            start = QPointF(fromRect.x() + fromRect.width()/2, fromRect.y() + fromRect.height());
            stop =  QPointF(toRect.x() + toRect.width()/2, toRect.y() + toRect.height());
            bendPoint = QPointF((fromRect.x() + toRect.x())/2 + 20, fromRect.y() + fromRect.height() + bezierBend);
            textPoint = QPointF(bendPoint.x() + 20, 0.25*(start.y()+2*bendPoint.y()+stop.y()) + 10);
        }

        QPainterPath path;
        path.moveTo(start);
        path.cubicTo(start, bendPoint, stop);
        //create arrow nose
        if(m_drawBackwardsArrowUp)
        {
            path.lineTo(stop.x(), stop.y() - 10);
            path.lineTo(stop);
            path.lineTo(stop.x() + 10, stop.y());
            m_drawBackwardsArrowUp = false;
        }
        else
        {
            path.lineTo(stop.x(), stop.y() + 10);
            path.lineTo(stop);
            path.lineTo(stop.x() + 10, stop.y());
            m_drawBackwardsArrowUp = true;
        }

        //add label
        path.addText(textPoint, Constants::SMALLER_TEXT_FONT, QString(label));

        return path;
    }

    QRectF CPainter::calculateRectForNode(const int stateNr)
    {
        using namespace Constants;
        QRectF rect;
        if(stateNr == 0)
            rect = QRectF(ELLIPSE_START_X, ELLIPSE_Y, ELLIPSE_RADIUS, ELLIPSE_RADIUS);
        else
        {
            const auto& relativePatternRect = m_patternRectItems[stateNr - 1];
            rect = QRectF( relativePatternRect->rect().x() + relativePatternRect->rect().width() - ELLIPSE_RADIUS/2,
                           ELLIPSE_Y, ELLIPSE_RADIUS, ELLIPSE_RADIUS);
        }

        return rect;
    }

    void CPainter::cleanWholeScene()
    {
        ABasePainter::cleanWholeScene();
        m_automaton.clear();
        m_view->scene()->clear();
    }

} // Automaton
} // Visualization
