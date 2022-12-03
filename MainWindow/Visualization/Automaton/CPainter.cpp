#include <QPainterPath>
#include "CPainter.h"

namespace Visualization
{
namespace Automaton
{
    CPainter::CPainter(QGraphicsView* view) :
        m_view(view)
    {
        m_view->setScene(std::make_unique<QGraphicsScene>().release());
    }

    void CPainter::drawBasicScene(const TextsPair& userTexts)
    {
        const auto& sourceText = userTexts.first;
        const auto& patternText = userTexts.second;
        drawRectsForText(sourceText, Constants::ERectType::SOURCE);
        drawRectsForText(patternText, Constants::ERectType::PATTERN);
        m_view->setSceneRect(m_view->scene()->itemsBoundingRect()); //fix to center rects to middle
        for(const auto& sourceRect : m_sourceRectItems)
            sourceRect->hide(); //we only need pattern to build automat
        for(const auto& patternRect : m_patternRectItems)
            patternRect->move(0, -250);

        m_drawBackwardsArrowUp = true;
    }

    void CPainter::paint(const Algorithms::Steps::CDrawAutomatonNode* drawNodeStep)
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

    void CPainter::paint(const Algorithms::Steps::CStartAutomaton* startAutomatonStep)
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

    void CPainter::paint(const Algorithms::Steps::CStateChangedAutomaton* stateChangedAutomatonStep)
    {
        clearAllHighlight();
        m_automaton[stateChangedAutomatonStep->m_stateNr]->setBrush(QBrush(Constants::ELLIPSE_HIGHLIGHT_COLOR));
        for(const auto& idx : stateChangedAutomatonStep->m_sourceIndices)
            m_sourceRectItems[idx]->setBrush(QBrush(Constants::ELLIPSE_HIGHLIGHT_COLOR)); //highligh them both with the same color
    }

    void CPainter::finishScene(const Indices& sourceIndices)
    {
        clearAllHighlight();
        for(const auto& rect : m_patternRectItems)
            rect->hide();
        Indices finalIndices = sourceIndices;
        auto color = Qt::green;
        if(sourceIndices.empty())
        {
            finalIndices.clear();
            color = Qt::red;
            for(auto i = 0; i < m_sourceRectItems.size(); ++i)
                finalIndices.push_back(i);
        }
        colorRects(m_sourceRectItems, finalIndices, color);
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

    void CPainter::colorRects(const std::vector<RectItemPtr>& collection, const Indices& indices, const Qt::GlobalColor color)
    {
        for(const auto& idx : indices)
            collection[idx]->setBrush(QBrush(color));
    }

    void CPainter::drawRectsForText(const std::string& text, const Constants::ERectType rectType)
    {
        using namespace Constants;
        assert(rectType == ERectType::SOURCE || (rectType == ERectType::PATTERN));

        const auto& scene = m_view->scene();
        const auto& rectYCoord = rectType == ERectType::SOURCE ? SOURCE_RECT_Y : PATTERN_RECT_Y;

        auto& destinationVec = rectType == ERectType::SOURCE ? m_sourceRectItems : m_patternRectItems;
        auto start = RECT_START_X;

        for(const auto& letter : text)
        {
            const auto& rectItem = std::make_shared<CRectItem>(
                        QRectF(start, rectYCoord, RECT_WIDTH, RECT_HEIGHT), std::string(1, letter));
            scene->addItem(rectItem.get());
            scene->addItem(rectItem->getText().get());
            destinationVec.push_back(rectItem);

            start += RECT_WIDTH;
        }
    }

    void CPainter::clearAllHighlight()
    {
        for(const auto& rect : m_sourceRectItems)
            rect->setBrush(QBrush(Constants::RECT_INITIAL_COLOR));
        for(const auto& rect : m_patternRectItems)
            rect->setBrush(QBrush(Constants::RECT_INITIAL_COLOR));
        for(const auto& node : m_automaton)
            node->setBrush(QBrush(Constants::ELLIPSE_INITIAL_COLOR));
    }

    void CPainter::cleanWholeScene()
    {
        m_sourceRectItems.clear();
        m_patternRectItems.clear();
        m_automaton.clear();
        m_view->scene()->clear();
    }

} //BruteForce
} //Visualization
