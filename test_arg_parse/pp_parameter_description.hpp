#ifndef PP_PARAMETER_DESCR_HPP
#define PP_PARAMETER_DESCR_HPP
#pragma once

#include <initializer_list>
#include <locale>
#include <set>
#include <string>
#include <type_traits>

#include "pp_parameter.hpp"

namespace program_parameters {
    
namespace details_ {
    struct LabelsHandler {
        using LabelIterator = std::initializer_list<std::string>::const_iterator;
        
        virtual void set_default_long(const std::string&) = 0;
        virtual void set_long(const std::string&, const std::string&) = 0;
        virtual void set_long(const std::string&, LabelIterator, LabelIterator) = 0;

        virtual void set_default_short(const std::string&) = 0;
        virtual void set_short(const std::string&, const std::string&) = 0;
        virtual void set_short(const std::string&, LabelIterator, LabelIterator) = 0;

        virtual void set_default_arg(const std::string&) = 0;
        virtual void set_arg(const std::string&, const std::string&) = 0;
    };
}

class ParameterDescriptionBase {
public:
    virtual ~ParameterDescriptionBase() {
    }
    
    const std::string& get_name() const {
        return name_;
    }
    
    ParameterDescriptionBase& long_label() {
        labels_.set_default_long(name_);
        return *this;
    }
    ParameterDescriptionBase& long_label(const std::string& label_str) {
        labels_.set_long(name_, label_str);
        return *this;
    }
    ParameterDescriptionBase& long_label(std::initializer_list<std::string> label_list) {
        labels_.set_long(name_, label_list.begin(), label_list.end());
        return *this;
    }

    ParameterDescriptionBase& short_label() {
        labels_.set_default_short(name_);
        return *this;
    }
    ParameterDescriptionBase& short_label(const std::string& label_str) {
        labels_.set_short(name_, label_str);
        return *this;
    }
    ParameterDescriptionBase& short_label(std::initializer_list<std::string> label_list) {
        labels_.set_short(name_, label_list.begin(), label_list.end());
        return *this;
    }

    ParameterDescriptionBase& arg_label() {
        labels_.set_default_arg(name_);
        return *this;
    }
    ParameterDescriptionBase& arg_label(const std::string& label_str) {
        labels_.set_arg(name_, label_str);
        return *this;
    }

    const std::string& get_help() const {
        return help_;
    }

    
protected:
    ParameterDescriptionBase(details_::LabelsHandler& labels_handler, std::string name, std::string help): 
            labels_(labels_handler), name_{std::move(name)}, help_{std::move(help)} {
    }
    
    details_::LabelsHandler&    labels_;
    std::string                 name_;
    std::string                 help_;
};

template <typename Type>
struct AlwaysValid {
public:
    bool operator()(Type&&) const {
        return true;
    }
};


template <typename Type, template <typename T> class Validator=AlwaysValid>
class ParameterDescription: public ParameterDescriptionBase {
public:
    using InitializerLabelList = std::initializer_list<std::string>;
    ParameterDescription(details_::LabelsHandler& labels_handler, const std::string& name, const std::string& help_str): 
            ParameterDescriptionBase{labels_handler, name, help_str} {
        long_label();
    }
    ParameterDescription(details_::LabelsHandler& labels_handler, const std::string& name, const std::string& help_str, InitializerLabelList label_list): 
            ParameterDescriptionBase{labels_handler, name, help_str, label_list} {
        long_label(label_list);
    }
};
   
template <typename Type, int add_args>
using OptionDescription = ParameterDescription<Option<Type, add_args>>;

template <typename Type>
using UniqueOptionDescription = ParameterDescription<UniqueOption<Type>>;
using FlagOptionDescription = ParameterDescription<FlagOption>;

template <typename Type>
using MultiOptionDescription = ParameterDescription<MultiOption<Type>>;

template <typename Type, int add_args>
using RequiredParameterDescription = ParameterDescription<RequiredParameter<Type, add_args>>;

template <typename Type>
using UniqueParameterDescription = ParameterDescription<UniqueParameter<Type>>;

}

#endif // PP_PARAMETER_DESCR_HPP
