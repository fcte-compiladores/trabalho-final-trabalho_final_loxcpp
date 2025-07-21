#include "Value.hpp"
#include <string>
#include <variant> // Necessário para std::visit e std::decay_t
#include <memory>  // Necessário para std::shared_ptr

// Declaração antecipada, caso LoxCallable.hpp não esteja incluído
class LoxCallable;

// A única definição da função agora vive aqui.
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
                // Futuramente, você pode querer chamar um método toString() do callable.
                return "<fn>";
            }
            return "unknown value";
        }, value);
    }

} // Fim do namespace lox