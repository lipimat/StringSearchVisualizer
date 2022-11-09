#include "CItem.h"

namespace Window
{
namespace ListElements
{

    CItem::CItem(ControllerPtr&& controllerPtr)
        : QListWidgetItem(QString::fromStdString(controllerPtr->getAlgorithmName()), nullptr , ItemType::UserType),
          m_controller(std::move(controllerPtr))
    {
        //create unique style for our items
        this->setHidden(false);
        this->setIcon(QIcon(QString(ItemConstants::ITEM_ICON_PATH.data())));
        this->setSizeHint(QSize(ItemConstants::ITEM_WIDTH, ItemConstants::ITEM_HEIGHT));
        this->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->setToolTip(QString(ItemConstants::ALGORITHM_TOOLTIP.data()));
        this->setBackground(QBrush(ItemConstants::NOT_CHOSEN_ITEM_BACKGROUND_COLOR));
    }

    QString CItem::getName() const
    {
        return QString::fromStdString(m_controller->getAlgorithmName());
    }

    QString CItem::getInfo() const
    {
        return QString::fromStdString(m_controller->getAlgorithmInfo());
    }

    void CItem::initializeVisualization(const Algorithms::TextsPair& userText) const
    {
        m_controller->initializeScene(userText);
    }

    void CItem::clearVisualization() const
    {
        m_controller->cleanScene();
    }

}//ListElements
}//Window
