#include "qfont.h"

#include "CTextItem.h"

namespace Window
{
namespace Visualization
{

    CTextItem::CTextItem(const std::string& text) :
        QGraphicsTextItem(QString::fromStdString(text))
    {
        this->setFont(QFont("Source Code Pro", 25));
    }

} //Visualization
} //Window
