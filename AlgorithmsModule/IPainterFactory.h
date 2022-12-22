#pragma once

namespace Visualization
{

namespace BruteForce
{
class IPainter;
using PainterPtr = std::unique_ptr<IPainter>;
} // BruteForce

namespace BoyerMoore
{
class IPainter;
using PainterPtr = std::unique_ptr<IPainter>;
} // BoyerMoore

namespace Automaton
{
class IPainter;
using PainterPtr = std::unique_ptr<IPainter>;
} // Automaton


    struct IPainterFactory
    {
        virtual BruteForce::PainterPtr createBruteForcePainter() const = 0;
        virtual BoyerMoore::PainterPtr createBoyerMoorePainter() const = 0;
        virtual Automaton::PainterPtr createAutomatonPainter() const = 0;
        virtual ~IPainterFactory() = default;
    };

    using PainterFactoryPtr = std::unique_ptr<IPainterFactory>;

} // Visualization
