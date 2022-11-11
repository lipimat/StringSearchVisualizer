#pragma once

#include <QGraphicsRectItem>

#include "CTextItem.h"

namespace Window
{
namespace Visualization
{

    class CRectItem : public QGraphicsRectItem
    {
    public:

        explicit CRectItem(const QRectF&);

        explicit CRectItem(const QRectF&, const std::string&);

        const TextItemPtr& getText() const;

    private:

        TextItemPtr m_text;
    };

    using RectItemPtr = std::shared_ptr<CRectItem>;

} //Visualization
} //Window