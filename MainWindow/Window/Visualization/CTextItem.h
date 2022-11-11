#pragma once

#include <QGraphicsTextItem>

namespace Window
{
namespace Visualization
{

    class CTextItem : public QGraphicsTextItem
    {
    public:
        explicit CTextItem(const std::string&);
    };

    using TextItemPtr = std::shared_ptr<CTextItem>;

} //Visualization
} //Window
