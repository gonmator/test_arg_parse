#ifndef PP_SYNTAX_HPP
#define PP_SNYTAX_HPP
#pragma once

#include <memory>
#include <new>
#include <vector>

#include "pp_parameter_description.hpp"

namespace program_parameters {

    namespace _details_ {
        template <typename T, class... Args>
        inline std::unique_ptr<T> make_unique(Args&&... args) {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }
    }
    
class Syntax {
public:
    Syntax() = default;
    Syntax(Syntax&&) = default;
    Syntax& operator=(Syntax&&) = default;
    
    Syntax(const Syntax&) = delete;
    Syntax& operator=(const Syntax&) = delete;

    template <typename Type, int min_args, int add_args, class Cast=DefStringCast<Type>>
    Syntax& new_parameter(const std::string& name, const std::string& help) {
        /** todo: checking if name is already in ? */
        using ThisParameter = Parameter<Type, min_args, add_args, Cast>;
        auto newParameterDescr = _details_::make_unique<ParameterDescription<ThisParameter>>(name, help);
        parameter_descriptions_.push_back(std::move(newParameterDescr));
        
        return *this;
    }
    
    template <typename Type, int add_args, class Cast=DefStringCast<Type>>
    Syntax& new_option(const std::string& name, const std::string& help) {
        return new_parameter<Type, 0, add_args, Cast>(name, help);
    }
    template <typename Type, class Cast=DefStringCast<Type>>
    Syntax& new_unique_option(const std::string& name, const std::string& help) {
        return new_option<Type, 1, Cast>(name, help);
    }
    Syntax& new_flag_option(const std::string& name, const std::string& help) {
        return new_unique_option<bool, DefStringCast<bool>>(name, help);
    }
    template <typename Type, class Cast=DefStringCast<Type>>
    Syntax& new_multi_option(const std::string& name, const std::string& help) {
        return new_option<Type, -1, Cast>(name, help);
    }
    template <typename Type, int add_args, class Cast=DefStringCast<Type>>
    Syntax& new_required_parameter(const std::string& name, const std::string& help) {
        return new_parameter<Type, 1, add_args, Cast>(name, help);
    }
    template <typename Type, class Cast=DefStringCast<Type>>
    Syntax& new_unique_parameter(const std::string& name, const std::string& help) {
        return new_parameter<Type, 1, 0, Cast>(name, help);
    }
    
    std::string get_usage() const {
        std::string usage{};
        for (const auto& pd: parameter_descriptions_) {
            usage.append(pd->get_usage()).append(" ");
        }
        
        return usage;
    }
protected:
private:
    std::vector<std::unique_ptr<ParameterDescriptionBase>>  parameter_descriptions_;
};

}


#endif // PP_SYNTAX_HPP
