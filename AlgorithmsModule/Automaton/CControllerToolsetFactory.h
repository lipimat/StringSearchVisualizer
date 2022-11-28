#pragma once

#include "IControllerToolsetFactory.h"

namespace Algorithms
{
namespace Automaton
{

    static constexpr std::string_view AUTOMATON_NAME = "Automaton";

    static constexpr std::string_view AUTOMATON_INFO =
            "<div class=\"bar\"><a name=\"SECTION0041\">Main features</a></div>"
            "<div class=\"mf\">"
            "<ul>"
            "<li>builds the minimal deterministic automaton recognizing the language <b>Σ</b><sup>*</sup><i>x</i></li>"
            "<li>extra space in <span style=\"white-space: nowrap\"><big><i><b>O</b></i></big>(<i>m</i>σ)</span> if the automaton is stored in a direct access table</li>"
            "<li>preprocessing phase in <span style=\"white-space: nowrap\"><big><i><b>O</b></i></big>(<i>m</i>σ)</span> time complexity</li>"
            "<li>searching phase in <span style=\"white-space: nowrap\"><big><i><b>O</b></i></big>(<i>n</i>)</span> time complexity if the automaton is stored in a direct access table, <span style=\"white-space: nowrap\"><big><i><b>O</b></i></big>(<i>n</i>log(σ))</span> otherwise</li>"
            "</ul>"
            "</div>"
            "<div class=\"bar\"><a name=\"SECTION0042\">Description</a></div>"
            "<div class=\"desc\">"
            "<p>Searching a word <i>x</i> with an automaton consists first in building the minimal Deterministic Finite Automaton (DFA) <span style=\"white-space: nowrap\"><big><em><b>&nbsp;A</b></em></big>(<i>x</i>)</span> recognizing the language <span style=\"white-space: nowrap\"><b>Σ</b><sup>*</sup><i>x</i></span>.</p>"
            "<dl>"
            "<dt>The DFA <span style=\"white-space: nowrap\"><big><em><b>&nbsp;A</b></em></big>(<i>x</i>) =(<em><b>Q</b></em>, <i>q</i><sub>0</sub>, <em><b>T</b></em>, <em><b>E</b></em>)</span> recognizing the language <span style=\"white-space: nowrap\"><b>Σ</b><sup>*</sup><i>x</i></span> is defined as follows:</dt>"
            "<dd>"
            "<table summary=\"case\">"
            "<tbody><tr>"
            "<td valign=\"BASELINE\">➸&nbsp;</td>"
            "<td valign=\"TOP\"><em><b>Q</b></em> is the set of all the prefixes of <i>x</i>: <span style=\"white-space: nowrap\"><em><b>Q</b></em>={ε, <i>x</i>[0], <i>x</i>[0 .. 1], ... , <i>x</i>[0 .. <i>m</i>-2], <i>x</i>}</span></td>"
            "</tr>"
            "</tbody></table>"
            "</dd>"
            "<dd>"
            "<table summary=\"case\">"
            "<tbody><tr>"
            "<td valign=\"BASELINE\">➸&nbsp;</td>"
            "<td valign=\"TOP\"><i>q</i><sub>0</sub>=ε</td>"
            "</tr>"
            "</tbody></table>"
            "</dd>"
            "<dd>"
            "<table summary=\"case\">"
            "<tbody><tr>"
            "<td valign=\"BASELINE\">➸&nbsp;</td>"
            "<td valign=\"TOP\"><em><b>T</b></em>={<i>x</i>}</td>"
            "</tr>"
            "</tbody></table>"
            "</dd>"
            "<dd>"
            "<table summary=\"case\">"
            "<tbody><tr>"
            "<td valign=\"BASELINE\">➸&nbsp;</td>"
            "<td valign=\"TOP\">for <i>q</i> in <em><b>Q</b></em> (<i>q</i> is a prefix of <i>x</i>) and <i>a</i> in <b>Σ</b>, <span style=\"white-space: nowrap\">(<i>q</i>, <i>a</i>, <i>qa</i>)</span> is in <em><b>E</b></em> if and only if <i>qa</i> is also a prefix of <i>x</i>, otherwise <span style=\"white-space: nowrap\">(<i>q</i>, <i>a</i>, <i>p</i>)</span> is in <em><b>E</b></em> such that <i>p</i> is the longest suffix of <i>qa</i> which is a prefix of <i>x</i></td>"
            "</tr>"
            "</tbody></table>"
            "</dd>"
            "</dl>"
            "<p align=\"justify\">The DFA <span style=\"white-space: nowrap\"><big><em><b>&nbsp;A</b></em></big>(<i>x</i>)</span> can be constructed in <big><i><b>O</b></i></big>(<i>m</i>+σ) time and <big><i><b>O</b></i></big>(<i>m</i>σ) space.</p>"
            "<p align=\"justify\">Once the DFA <span style=\"white-space: nowrap\"><big><em><b>&nbsp;A</b></em></big>(<i>x</i>)</span> is build, searching for a word <i>x</i> in a text <i>y</i> consists in parsing the text <i>y</i> with the DFA <span style=\"white-space: nowrap\"><big><em><b>&nbsp;A</b></em></big>(<i>x</i>)</span> beginning with the initial state <i>q</i><sub>0</sub>. Each time the terminal state is encountered an occurrence of <i>x</i> is reported.</p>"
            "<p align=\"justify\">The searching phase can be performed in <big><i><b>O</b></i></big>(<i>n</i>) time if the automaton is stored in a direct access table, in <span style=\"white-space: nowrap\"><big><i><b>O</b></i></big>(<i>n</i>log(σ))</span> otherwise.</p>"
            "<a href=\"http://www-igm.univ-mlv.fr/~lecroq/string/node4.html#SECTION0040\">More information here...</a>"
            "</div>";

    struct CControllerToolsetFactory final : IControllerToolsetFactory
    {
        std::string_view createName() const override;
        std::string_view createInfo() const override;
        StepsExecutorPtr createStepsExecutor() const override;
        Visualization::PainterPtr createPainter(const Visualization::PainterFactoryPtr&) const override;
    };

} //Automaton
} //Algorithms
