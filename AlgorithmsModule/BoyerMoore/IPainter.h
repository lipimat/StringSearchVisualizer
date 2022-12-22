#pragma once

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

    using TextsPair = std::pair<const std::string, const std::string>;
    using Indices = std::vector<int>;

    class IPainter
    {
    public:
        virtual void drawBasicScene(const TextsPair&) = 0;
        virtual void paint(const Algorithms::Steps::CComparison<PainterPtr>*) = 0;
        virtual void paint(const Algorithms::Steps::CMovePattern<PainterPtr>*) = 0;
        virtual void finishScene(const Indices&) = 0;
        virtual void cleanWholeScene() = 0;
        virtual ~IPainter() = default;
    };



} // BoyerMoore
} // Visualization
