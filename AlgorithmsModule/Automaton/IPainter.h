#pragma once

#include "../IBasePainter.h"

namespace Algorithms
{
namespace Steps
{
template<class P>
class CDrawAutomatonNode;
template<class P>
class CStartAutomaton;
template<class P>
class CStateChangedAutomaton;
} //Steps
} //Algorithms

namespace Visualization
{
namespace Automaton
{
class IPainter;
using PainterPtr = std::unique_ptr<IPainter>;

    class IPainter : public IBasePainter
    {
    public:
        virtual void paint(const Algorithms::Steps::CDrawAutomatonNode<PainterPtr>*) = 0;
        virtual void paint(const Algorithms::Steps::CStartAutomaton<PainterPtr>*) = 0;
        virtual void paint(const Algorithms::Steps::CStateChangedAutomaton<PainterPtr>*) = 0;
    };

} // Automaton
} // Visualization
