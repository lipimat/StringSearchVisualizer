#pragma once

#include "IStep.h"

namespace Algorithms
{
namespace Steps
{

    class CMovePattern final : public IStep
    {
    public:
        explicit CMovePattern(const int);
        void accept(const Visualization::PainterPtr&) const override;
        bool operator==(const CMovePattern&);

        const int m_moveBy;
    };

} //Steps
} //Algorithms
