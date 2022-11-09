#include "qfont.h"

#include "CTextItem.h"
#include "VisualizationConstants.h"

namespace Window
{
namespace Visualization
{

    CTextItem::CTextItem(const std::string& text) :
        QGraphicsTextItem(QString::fromStdString(text))
    {
        this->setFont(Constants::TEXT_FONT);
    }

} //Visualization
} //Window
