#pragma once

#include "IControllerToolsetFactory.h"

namespace Algorithms
{
namespace BoyerMoore
{

    static constexpr std::string_view BOYER_MOORE_NAME = "Booyer-Moore";

    static constexpr std::string_view BOYER_MOORE_INFO =
            "<div class=\"bar\"><a name=\" SECTION00141\">Main features</a></div>"
            "<div class=\"mf\">"
            "<ul>"
            "<li>performs the comparisons from right to left;</li>"
            "<li>preprocessing phase in <span style=\"white-space: nowrap\"><big><i><b>O</b></i></big>(<i>m</i>+<img alt=\"sigma\" src=\"images/psigma.gif\">)</span> time and space complexity;</li>"
            "<li>searching phase in <span style=\"white-space: nowrap\"><big><i><b>O</b></i></big>(<i>m</i><i>n</i>)</span> time complexity;</li>"
            "<li><span style=\"white-space: nowrap\">3<i>n</i></span> text character comparisons in the worst case when searching for a non periodic pattern;</li>"
            "<li><span style=\"white-space: nowrap\"><big><i><b>O</b></i></big>(<i>n</i> / <i>m</i>)</span> best performance.</li>"
            "</ul>"
            "</div>"
            "<div class=\"bar\"><a name=\"SECTION00142\">Description</a></div>"
            "<div class=\"desc\">"
            "<p align=\"justify\">The Boyer-Moore algorithm is considered as the most efficient string-matching algorithm in usual applications. A simplified version of it or the entire algorithm is often implemented in text editors for the «search» and «substitute» commands.</p>"
            "<p align=\"justify\">The algorithm scans the characters of the pattern from right to left beginning with the rightmost one. In case of a mismatch (or a complete match of the whole pattern) it uses two precomputed functions to shift the window to the right. These two shift functions are called the <em><b>good-suffix shift</b></em> (also called matching shift and the <em><b>bad-character shift</b></em> (also called the occurrence shift).</p>"
            "<p align=\"justify\">Assume that a mismatch occurs between the character <span style=\"white-space: nowrap\"><i>x</i>[<i>i</i>]=<i>a</i></span> of the pattern and the character <span style=\"white-space: nowrap\"><i>y</i>[<i>i</i>+<i>j</i>]=<i>b</i></span> of the text during an attempt at position <span style=\"white-space: nowrap\"><i>j</i></span>.<br>"
            "Then, <span style=\"white-space: nowrap\"><i>x</i>[<i>i</i>+1 .. <i>m</i>-1]=<i>y</i>[<i>i</i>+<i>j</i>+1 .. <i>j</i>+<i>m</i>-1]=u</span> and <span style=\"white-space: nowrap\"><i>x</i>[<i>i</i>]!=y[<i>i</i>+<i>j</i>]</span>. The good-suffix shift consists in aligning the segment <span style=\"white-space: nowrap\"><i>y</i>[<i>i</i>+<i>j</i>+1 .. <i>j</i>+<i>m</i>-1]=<i>x</i>[<i>i</i>+1 .. <i>m</i>-1]</span> with its rightmost occurrence in <i>x</i> that is preceded by a character different from <span style=\"white-space: nowrap\"><i>x</i>[<i>i</i>]</p>"
            "</div>";

    struct CControllerToolsetFactory final : IControllerToolsetFactory
    {
        std::string_view createName() const override;
        std::string_view createInfo() const override;
        StepsExecutorPtr createStepsExecutor() const override {};
        Visualization::PainterPtr createPainter(const Visualization::PainterFactoryPtr&) const override {};
    };

} //BoyerMoore
} //Algorithms
