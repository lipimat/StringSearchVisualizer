#include "qfont.h"

#include "CTextItem.h"
#include "../Constants.h"

namespace Visualization
{

    CTextItem::CTextItem(const std::string& text) :
        QGraphicsTextItem(QString::fromStdString(text))
    {
        this->setFont(Constants::TEXT_FONT);
    }

} //Visualization
