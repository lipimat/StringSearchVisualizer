#include "qbrush.h"

#include "CRectItem.h"
#include "Constants.h"

namespace Window
{
namespace Visualization
{

    CRectItem::CRectItem(const QRectF& rect) :
        QGraphicsRectItem(rect)
    {
        this->setBrush(QBrush(Constants::RECT_INITIAL_COLOR));
    }

    CRectItem::CRectItem(const QRectF& rect, const std::string& text) :
        CRectItem(rect)
    {
        m_text = std::make_shared<CTextItem>(text);

        // center this text with our rect
        const auto& thisRect = this->boundingRect();
        const auto& textRect = m_text->boundingRect();

        m_text->setPos(thisRect.x() + (thisRect.width() - textRect.width())/2,
                       thisRect.y() + (thisRect.height() - textRect.height())/2);
    }

    const TextItemPtr& CRectItem::getText() const
    {
        return m_text;
    }

} //Visualization
} //Window
