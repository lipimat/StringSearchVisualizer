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
    }

    void CPainter::paint(const Algorithms::Steps::CDrawAutomatonNode* drawNodeStep)
    {
        using namespace Constants;
        const auto& scene = m_view->scene();
        const auto& currentSourceRect = m_sourceRectItems[drawNodeStep->m_stateNumber];
        const auto& currentPatternRect = m_patternRectItems[drawNodeStep->m_stateNumber];

        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(
                    currentSourceRect->rect().x() + currentSourceRect->rect().width()/2 - 30,
                    currentPatternRect->rect().y(), 60 , 60);

        circle->setBrush(QBrush(Qt::white));
        scene->addItem(circle);
        const auto& text = new CTextItem(std::to_string(drawNodeStep->m_stateNumber));
        const auto& thisRect = circle->boundingRect();
        const auto& textRect = text->boundingRect();

        text->setPos(thisRect.x() + (thisRect.width() - textRect.width())/2,
                       thisRect.y() + (thisRect.height() - textRect.height())/2);
        scene->addItem(text);
        QPainterPath path;
        //strzalka w prawo
//        path.moveTo(circle->boundingRect().x() + circle->boundingRect().width(),
//                    circle->boundingRect().y() + circle->boundingRect().height()/2);
//        path.lineTo(circle->boundingRect().x() + circle->boundingRect().width() + 20,
//                     circle->boundingRect().y() + circle->boundingRect().height()/2);
//        path.lineTo(circle->boundingRect().x() + circle->boundingRect().width() + 10,
//                     circle->boundingRect().y() + circle->boundingRect().height()/2 - 10);
//        path.lineTo(circle->boundingRect().x() + circle->boundingRect().width() + 20,
//                     circle->boundingRect().y() + circle->boundingRect().height()/2);
//        path.lineTo(circle->boundingRect().x() + circle->boundingRect().width() + 10,
//                     circle->boundingRect().y() + circle->boundingRect().height()/2 + 10);
        // krzywa szczala
//        path.moveTo(circle->boundingRect().x() + circle->boundingRect().width()/2,
//                    circle->boundingRect().y());
//        path.cubicTo(QPointF(circle->boundingRect().x() + circle->boundingRect().width()/2,
//                             circle->boundingRect().y()),
//                     QPointF(circle->boundingRect().x() + circle->boundingRect().width()/2 - 30,
//                             circle->boundingRect().y() -50),
//                     QPointF(circle->boundingRect().x() + circle->boundingRect().width()/2 - 60,
//                             circle->boundingRect().y()));
//        path.lineTo(circle->boundingRect().x() + circle->boundingRect().width()/2 - 60,
//                    circle->boundingRect().y() - 10);
//        path.lineTo(circle->boundingRect().x() + circle->boundingRect().width()/2 - 60,
//                    circle->boundingRect().y());
//        path.lineTo(circle->boundingRect().x() + circle->boundingRect().width()/2 - 50,
//                    circle->boundingRect().y());
        scene->addPath(path);
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
    }

    void CPainter::cleanWholeScene()
    {
        m_sourceRectItems.clear();
        m_patternRectItems.clear();
        m_view->scene()->clear();
    }

} //BruteForce
} //Visualization
