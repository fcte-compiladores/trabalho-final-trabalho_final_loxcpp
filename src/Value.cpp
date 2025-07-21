#include "Value.hpp"
#include <string>
#include <variant> 
#include <memory>  

class LoxCallable;

namespace lox {

    std::string valueToString(const Value& value) {
        return std::visit([](const auto& v) -> std::string {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, std::monostate>) {
                return "nil";
            } else if constexpr (std::is_same_v<T, bool>) {
                return v ? "true" : "false";
            } else if constexpr (std::is_same_v<T, double>) {
                std::string s = std::to_string(v);
                s.erase(s.find_last_not_of('0') + 1, std::string::npos);
                if (s.back() == '.') s.pop_back();
                return s;
            } else if constexpr (std::is_same_v<T, std::string>) {
                return v;
            } else if constexpr (std::is_same_v<T, std::shared_ptr<LoxCallable>>) {
                return "<fn>";
            }
            return "unknown value";
        }, value);
    }

} 