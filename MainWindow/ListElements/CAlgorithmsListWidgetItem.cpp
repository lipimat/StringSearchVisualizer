#include "CAlgorithmsListWidgetItem.h"

namespace Window
{
namespace AlgorithmsListItem
{

    CAlgorithmsListWidgetItem::CAlgorithmsListWidgetItem(const std::string& itemName)
    {
        this->setText(QString::fromStdString(itemName));
        this->setHidden(false);
    }

}//AlgorithmsListItem
}//Window
