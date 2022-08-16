#pragma once

#include "IAlgorithmsListWidgetItem.h"

namespace Window
{
namespace AlgorithmsListItem
{

    class CAlgorithmsListWidgetItem : public IAlgorithmsListWidgetItem
    {
    public:

        CAlgorithmsListWidgetItem(const std::string&);

        virtual ~CAlgorithmsListWidgetItem() = default;
    };

}//AlgorithmsListItem
}//Window
