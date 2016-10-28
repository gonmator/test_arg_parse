#ifndef PP_PARAMETER_HPP
#define PP_PARAMETER_HPP
#pragma once

#include <sstream>
#include <string>

namespace program_parameters {

namespace {
    template <typename Type, Type def_value>
    class ValueToType {
        using type = Type;
        static constexpr Type   value = def_value;
    };
    
    template <typename T>
    class DefStringCast {
        std::string operator()(const T& v) const {
            return static_cast<std::stringstream&>(std::stringstream{} << v).str();
        }
        T operator()(const std::string& str) const {
            T   v;
            std::stringstream{str} >> v;
            return v;
        }
    };
    
    template <>
    class DefStringCast<std::string> {
        std::string operator()(std::string&& str) const {
            return std::forward<std::string>(str);
        }
    };
}   

/** ParameterBase */

struct ParameterBase {
    
};

/** ParameterHelper */
template <typename Type, int min_args, int add_args, class Cast=DefStringCast<Type>>
struct ParameterHelper {
    static constexpr unsigned int min_arguments() { return min_args; }
    static constexpr int max_arguments() { return (add_args == -1 ? -1 : min_args + add_args); }
    static constexpr bool required() { return min_args >= 1; }
    static constexpr bool unique() { return min_args + add_args == 1; }
    
    static constexpr bool is_optional = false;
};

/** Parameter */
 
template <typename Type, int min_args, int add_args, class Cast=DefStringCast<Type>>
class Parameter: public ParameterBase, ParameterHelper<Type, min_args, add_args, Cast> {
};

template <typename Type_, int add_args, class Cast>
class Parameter<Type_, 0, add_args, Cast>: public ParameterHelper<Type_, 0, add_args, Cast> {
public:
    using Type = Type_;
    
    static constexpr bool is_optional = true;
    
    Parameter() {
    }
};

// Invalid Null Parameter, with minimal of arguments and maximum of arguments = 0
template <typename Type, class Cast>
class Parameter<Type, 0, 0, Cast>;



template <typename Type, int add_args>
using Option = Parameter<Type, 0, add_args, DefStringCast<Type>>;

template <typename Type>
using UniqueOption = Option<Type, 1>;
using FlagOption = UniqueOption<bool>;

template <typename Type>
using MultiOption = Option<Type, -1>;

template <typename Type, int add_args>
using RequiredParameter = Parameter<Type, 1, add_args, DefStringCast<Type>>;

template <typename Type>
using UniqueParameter = Parameter<Type, 1, 0, DefStringCast<Type>>;

}


#endif // PP_PARAMETER_HPP
