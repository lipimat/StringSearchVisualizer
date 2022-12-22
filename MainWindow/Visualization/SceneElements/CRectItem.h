#pragma once

#include "CTextItem.h"

namespace Visualization
{

    class CRectItem : public QGraphicsRectItem
    {
    public:

        explicit CRectItem(const QRectF&);

        explicit CRectItem(const QRectF&, const std::string&);

        const TextItemPtr& getText() const;

        void hide();

        void show();

        void move(const int /*dx*/, const int /*dy*/);

    private:

        TextItemPtr m_text;
    };

    using RectItemPtr = std::shared_ptr<CRectItem>;

} // Visualization
