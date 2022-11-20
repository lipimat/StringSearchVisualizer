#pragma once

namespace Algorithms
{
namespace Steps
{
class CComparison;
class CMovePattern;
} //Steps
} //Algorithms

namespace Visualization
{

    using TextsPair = std::pair<const std::string, const std::string>;
    using Indices = std::vector<int>;

    class IPainter
    {
    public:
        virtual void drawBasicScene(const TextsPair&) = 0;
        virtual void paint(const Algorithms::Steps::CComparison*) = 0;
        virtual void paint(const Algorithms::Steps::CMovePattern*) = 0;
        virtual void finishScene(const Indices&) = 0;
        virtual void cleanWholeScene() = 0;
        virtual ~IPainter() = default;
    };

    using PainterPtr = std::unique_ptr<IPainter>;

} // Visualization
