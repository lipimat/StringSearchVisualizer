#pragma once

#include <string_view>

namespace Algorithms
{

    class IController
    {
    public:

        virtual const std::string& getAlgorithmName() const = 0;
        virtual const std::string& getAlgorithmInfo() const = 0;
        virtual void initializeScene() const = 0;
        virtual ~IController() = default;

    };

} //Algorithms
