#pragma once

namespace Visualization
{

    using TextsPair = std::pair<const std::string, const std::string>;
    using Indices = std::vector<int>;

    class IBasePainter
    {
    public:
        virtual void drawBasicScene(const TextsPair&) = 0;
        virtual void finishScene(const Indices&) = 0;
        virtual void cleanWholeScene() = 0;
        virtual ~IBasePainter() = default;
    };

} // Visualization
