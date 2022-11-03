#pragma once

#include <QListWidgetItem>

#include "../AlgorithmsModule/IController.h"

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
        static constexpr QColor CHOSEN_ITEM_BACKGROUND_COLOR = QColor(114,210,144);
    }

    class CItem : public QListWidgetItem
    {
    public:

        explicit CItem(const std::string&, Algorithms::IController*);
        Algorithms::IController* getController() const;
        virtual ~CItem() = default;

    private:

         Algorithms::IController* m_controller;
    };

}//ListElements
}//Window
