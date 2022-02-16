#pragma once

#include "../util/State.h"
#include "Registry.h"

#include <functional>

namespace Registries {

class CommandRegistry final : public Registry<std::function<void(State &, std::vector<std::string_view>)>> {
public:
    CommandRegistry()
        : Registry("CommandRegistry")
    {
    }
};

}
