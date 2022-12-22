#include "ABasePainter.h"

namespace Visualization
{

    ABasePainter::ABasePainter(QGraphicsView* view) :
        m_view(view)
    {
        assert(m_view != nullptr);
        m_view->setScene(std::make_unique<QGraphicsScene>().release());
    }

    void ABasePainter::drawBasicScene(const TextsPair& userTexts)
    {
        const auto& sourceText = userTexts.first;
        const auto& patternText = userTexts.second;
        drawRectsForText(sourceText, Constants::ERectType::SOURCE);
        drawRectsForText(patternText, Constants::ERectType::PATTERN);
        m_view->setSceneRect(m_view->scene()->itemsBoundingRect()); //fix to center rects to middle
    }

    void ABasePainter::finishScene(const Indices& sourceIndices)
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

    void ABasePainter::cleanWholeScene()
    {
        m_sourceRectItems.clear();
        m_patternRectItems.clear();
    }

    void ABasePainter::colorRects(const std::vector<RectItemPtr>& collection, const Indices& indices, const Qt::GlobalColor color)
    {
        for(const auto& idx : indices)
            collection[idx]->setBrush(QBrush(color));
    }

    void ABasePainter::drawRectsForText(const std::string& text, const Constants::ERectType rectType)
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

    void ABasePainter::clearAllHighlight()
    {
        for(const auto& rect : m_sourceRectItems)
            rect->setBrush(QBrush(Constants::RECT_INITIAL_COLOR));
        for(const auto& rect : m_patternRectItems)
            rect->setBrush(QBrush(Constants::RECT_INITIAL_COLOR));
    }

} // Visualization
