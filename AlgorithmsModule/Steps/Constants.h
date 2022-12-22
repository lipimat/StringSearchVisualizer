#pragma once

namespace Algorithms
{
namespace Steps
{

    enum class EAlgorithmState
    {
        CONTINUE,
        FINISHED
    };

    enum class EComparisonType
    {
        MATCH,
        MISMATCH,
        IDLE
    };

    using Indices = std::vector<int>;

} // Steps
} // Algorithms
