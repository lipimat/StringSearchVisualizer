#pragma once

#include "../BruteForce/CTextItem.h"

namespace Visualization
{

    class CEllipseItem : public QGraphicsEllipseItem
    {
    public:

        explicit CEllipseItem(const QRectF&);

        explicit CEllipseItem(const QRectF&, const std::string&);

        const TextItemPtr& getText() const;

        void hide();

        void move(const int dx, const int dy);

    private:

        TextItemPtr m_text;
    };

    using EllipseItemPtr = std::shared_ptr<CEllipseItem>;

} //Visualization
