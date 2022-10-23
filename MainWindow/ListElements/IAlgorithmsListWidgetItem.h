#pragma once

#include <QListWidgetItem>

namespace Window
{
namespace AlgorithmsListItem
{
    class IAlgorithmsListWidgetItem : public QListWidgetItem
    {
    public:

        virtual ~IAlgorithmsListWidgetItem() = default;
    };
}//AlgorithmsListItem
}//Window
