#pragma once

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

    using TextsPair = std::pair<const std::string, const std::string>;
    using Indices = std::vector<int>;

    class IPainter
    {
    public:
        virtual void drawBasicScene(const TextsPair&) = 0;
        virtual void paint(const Algorithms::Steps::CDrawAutomatonNode<PainterPtr>*) = 0;
        virtual void paint(const Algorithms::Steps::CStartAutomaton<PainterPtr>*) = 0;
        virtual void paint(const Algorithms::Steps::CStateChangedAutomaton<PainterPtr>*) = 0;
        virtual void finishScene(const Indices&) = 0;
        virtual void cleanWholeScene() = 0;
        virtual ~IPainter() = default;
    };

} // Automaton
} // Visualization
