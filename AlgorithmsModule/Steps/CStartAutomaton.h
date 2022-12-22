#pragma once

#include "IStep.h"

namespace Algorithms
{
namespace Steps
{

    template<class Painter>
    class CStartAutomaton final : public IStep<Painter>
    {
    public:
        void accept(const Painter&) const override;
    };

} // Steps
} // Algorithms
