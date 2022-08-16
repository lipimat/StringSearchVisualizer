#ifndef ALGORITHMSMODULE_H
#define ALGORITHMSMODULE_H
#include <string_view>

static constexpr std::string_view MODULE_NAME = "GHello!";

class AlgorithmsModule
{
public:
    AlgorithmsModule();
    static constexpr std::string_view getName() { return MODULE_NAME; }
};

#endif // ALGORITHMSMODULE_H
