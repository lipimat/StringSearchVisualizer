#pragma once

#include "IStep.h"

namespace Algorithms
{
namespace Steps
{
    using NodeRelations = std::vector< std::pair<int, char> >;

    template<class Painter>
    class CDrawAutomatonNode final : public IStep<Painter>
    {
    public:
        explicit CDrawAutomatonNode(const int, const NodeRelations&);
        void accept(const Painter&) const override;
        bool operator==(const CDrawAutomatonNode&);

        const int m_stateNumber;
        const NodeRelations m_nodeRelations;
    };

} // Steps
} // Algorithms
