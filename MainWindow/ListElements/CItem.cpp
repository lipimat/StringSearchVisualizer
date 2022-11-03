#include "CItem.h"

namespace Window
{
namespace ListElements
{

    CItem::CItem(const std::string& itemName, Algorithms::IController* controller)
        : QListWidgetItem(QString::fromStdString(itemName), nullptr , ItemType::UserType), m_controller(controller)
    {
        //create unique style for our items
        this->setHidden(false);
        this->setIcon(QIcon(QString(ItemConstants::ITEM_ICON_PATH.data())));
        this->setSizeHint(QSize(ItemConstants::ITEM_WIDTH, ItemConstants::ITEM_HEIGHT));
        this->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->setToolTip(QString(ItemConstants::ALGORITHM_TOOLTIP.data()));
        this->setBackground(QBrush(ItemConstants::NOT_CHOSEN_ITEM_BACKGROUND_COLOR));
    }

    Algorithms::IController* CItem::getController() const
    {
        return m_controller;
    }

}//ListElements
}//Window
