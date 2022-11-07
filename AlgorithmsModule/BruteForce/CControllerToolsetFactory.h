#pragma once

#include "../IControllerToolsetFactory.h"
#include "AVisualizationPainter.h"

namespace Algorithms
{
namespace BruteForce
{

    static constexpr std::string_view BRUTE_FORCE_NAME = "Brute Force";

    static constexpr std::string_view BRUTE_FORCE_INFO =
            "<div class=\"bar\"><a name=\"SECTION0031\">Main features</a></div>"

            "<div class=\"mf\">"
            "<ul>"
            "<li>no preprocessing phase;</li>"

            "<li>constant extra space needed;</li>"

            "<li>always shifts the window by exactly 1 position to the right;</li>"

            "<li>comparisons can be done in any order;</li>"

            "<li>searching phase in <big><i><b>O</b></i></big>(<i>m</i><i>n</i>) time complexity;</li>"

            "<li>2<i>n</i> expected text characters comparisons.</li>"
            "</ul>"
            "</div>"

            "<div class=\"bar\"><a name=\"SECTION0032\">Description</a></div>"

            "<div class=\"desc\">"
            "<p align=\"justify\">The brute force algorithm consists in checking, at all positions in the text between 0 and <i>n</i>-<i>m</i>, whether an occurrence of the pattern starts there or not. Then, after each attempt, it shifts the pattern by exactly one position to the right.</p>"

            "<p align=\"justify\">The brute force algorithm requires no preprocessing phase, and a constant extra space in addition to the pattern and the text. During the searching phase the text character comparisons can be done in any order. The time complexity of this searching phase is <big><i><b>O</b></i></big>(<i>m</i><i>n</i>) (when searching for <big><tt>a</tt></big><sup><i>m</i>-1</sup><big><tt>b</tt></big> in <big><tt>a</tt></big><sup><i>n</i></sup> for instance). The expected number of text character comparisons is 2<i>n</i>.</p>"
            "</div>";

    struct CControllerToolsetFactory final : IControllerToolsetFactory
    {
        std::string_view createName() const override;
        std::string_view createInfo() const override;
        AVisualizationPainter* createPainter(Window::IVisualizationWidget*) const override;
    };

} //BruteForce
} //Algorithms
