#pragma once

#include "../IBasePainter.h"

namespace Algorithms
{
namespace Steps
{
template<class P>
class CComparison;
template<class P>
class CMovePattern;
} //Steps
} //Algorithms

namespace Visualization
{
namespace BoyerMoore
{
class IPainter;
using PainterPtr = std::unique_ptr<IPainter>;

    class IPainter : public IBasePainter
    {
    public:
        virtual void paint(const Algorithms::Steps::CComparison<PainterPtr>*) = 0;
        virtual void paint(const Algorithms::Steps::CMovePattern<PainterPtr>*) = 0;
    };

} // BoyerMoore
} // Visualization
