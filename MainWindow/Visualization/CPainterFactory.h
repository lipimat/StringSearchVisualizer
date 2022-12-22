#pragma once

#include "../AlgorithmsModule/IPainterFactory.h"
#include "Visualization/BruteForce/CPainter.h"
#include "Visualization/BoyerMoore/CPainter.h"
#include "Visualization/Automaton/CPainter.h"

namespace Visualization
{

    struct CPainterFactory final : IPainterFactory
    {
        CPainterFactory(QGraphicsView*);
        BruteForce::PainterPtr createBruteForcePainter() const override;
        BoyerMoore::PainterPtr createBoyerMoorePainter() const override;
        Automaton::PainterPtr createAutomatonPainter() const override;

    private:

        QGraphicsView* m_view;

    };

} //Visualization
