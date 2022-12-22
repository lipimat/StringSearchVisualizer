#pragma once

#include "IStep.h"

namespace Algorithms
{
namespace Steps
{

    template<class Painter>
    class CMovePattern final : public IStep<Painter>
    {
    public:
        explicit CMovePattern(const int);
        void accept(const Painter&) const override;
        bool operator==(const CMovePattern&);

        const int m_moveBy;
    };

} // Steps
} // Algorithms
