#pragma once

#include <string>
#include <variant>
#include <memory>

// Forward declaration
class LoxCallable;

namespace lox {

    using Value = std::variant<
        std::monostate, // nil
        bool,
        double,
        std::string,
        std::shared_ptr<LoxCallable>
    >;

    // Apenas a declaração da função.
    std::string valueToString(const Value& value);

} // Fim do namespace lox