#pragma once

#include <string_view>
#include <memory>

namespace Algorithms
{

    using TextsPair = std::pair<const std::string, const std::string>;

    class IController
    {
    public:

        virtual const std::string& getAlgorithmName() const = 0;
        virtual const std::string& getAlgorithmInfo() const = 0;
        virtual void initializeScene(const TextsPair&) const = 0;
        virtual void cleanScene() const = 0;
        virtual bool nextStep() const = 0;
        virtual ~IController() = default;

    };

    using ControllerPtr = std::unique_ptr<IController>;

} //Algorithms
