#include "CEllipseItem.h"
#include "Constants.h"

namespace Visualization
{
    CEllipseItem::CEllipseItem(const QRectF& rect) :
        QGraphicsEllipseItem(rect)
    {
        this->setBrush(QBrush(Constants::ELLIPSE_INITIAL_COLOR));
    }

    CEllipseItem::CEllipseItem(const QRectF& rect, const std::string& text) :
        CEllipseItem(rect)
    {
        m_text = std::make_shared<CTextItem>(text);

        // center this text with our rect
        const auto& thisRect = this->boundingRect();
        const auto& textRect = m_text->boundingRect();

        m_text->setPos(thisRect.x() + (thisRect.width() - textRect.width())/2,
                       thisRect.y() + (thisRect.height() - textRect.height())/2);
    }

    const TextItemPtr& CEllipseItem::getText() const
    {
        return m_text;
    }

    void CEllipseItem::hide()
    {
        QGraphicsEllipseItem::hide();
        this->m_text->hide();
    }

    void CEllipseItem::move(const int dx, const int dy)
    {
        this->moveBy(dx, dy);
        m_text->moveBy(dx, dy);
    }

} // Visualization
