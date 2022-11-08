#pragma once

#include <string>

#include "IController.h"
#include "IControllerToolsetFactory.h"

namespace Algorithms
{

    class CController final : public IController
    {
    public:

        CController(const IControllerToolsetFactory* const);
        const std::string& getAlgorithmName() const override;
        const std::string& getAlgorithmInfo() const override;
        void initializeScene() const override;

    private:

        std::string m_algorithmName;
        std::string m_algorithmInfo;
    };

} //Algorithms
