#pragma once

#include <QListWidgetItem>

namespace Window
{
namespace ListElements
{

    namespace ItemConstants
    {
        static constexpr int ITEM_WIDTH = 300;
        static constexpr int ITEM_HEIGHT = 100;
        static constexpr std::string_view ALGORITHM_TOOLTIP = "Selectable algorithm";
        static constexpr std::string_view ITEM_ICON_PATH = ":/ItemIcon/ItemIcon.png";
        static constexpr QColor NOT_CHOSEN_ITEM_BACKGROUND_COLOR = QColor(255,204,203);
        static constexpr QColor CHOSEN_ITEM_BACKGROUND_COLOR = QColor(114,238,144);
    }

    class CAlgorithmsListWidgetItem : public QListWidgetItem
    {
    public:

        CAlgorithmsListWidgetItem(const std::string&);

        virtual ~CAlgorithmsListWidgetItem() = default;
    };

}//AlgorithmsListItem
}//Window
