#ifndef PP_PARAMETER_DESCRIPTIONS_HPP
#define PP_PARAMETER_DESCRIPTIONS_HPP
#pragma once

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <map>
#include <memory>
#include <ostream>
#include <string>

#include "pp_formatter.hpp"
#include "pp_help_policy.hpp"
#include "pp_parameter_description.hpp"

namespace program_parameters {
    
namespace details_ {
    static std::string make_long_label(const std::string& name) {
        return name;
    }
    static std::string make_short_label(const std::string& name) {
        if (!name.empty()) {
            return name.substr(0, 1);
        }
        return std::string{};
    }
    static std::string make_arg_label(const std::string& name) {
        std::string rv(name);
        std::use_facet<std::ctype<char>>(std::locale{"C"}).toupper(&rv[0], &rv[rv.size()]);
        return rv;
    }

    template <std::string (*Defaulter)(const std::string&), class Map>
    struct BaseLabels {
        using LabelIterator = std::initializer_list<std::string>::const_iterator;
        
        virtual void set_default(const std::string& name) {
            labels_.insert(std::make_pair(name, Defaulter(name)));
        }
        virtual void set(const std::string& name, const std::string& label) {
            labels_.insert(std::make_pair(name, label));
        }
        virtual void set(const std::string& name, const std::string* first_label, const std::string* last_label) {
            std::for_each(first_label, last_label, [this, &name](const std::string& label) {
                labels_.insert(std::make_pair(name, label));
            });
        }
        
        Map labels_;
    };    
}
    


template <std::string (*Defaulter)(const std::string&)>
using SingleLabels = details_::BaseLabels<Defaulter, std::map<std::string, std::string>>;

template <std::string (*Defaulter)(const std::string&)>
using MultipleLabels = details_::BaseLabels<Defaulter, std::multimap<std::string, std::string>>;

using MultipleLongLabels = MultipleLabels<details_::make_long_label>;
using MultipleShortLabels = MultipleLabels<details_::make_short_label>;
using DefaultArgLabels = SingleLabels<details_::make_arg_label>;

template <class LongLabels, class ShortLabels, class ArgLabels>
struct LabelsPolicy: details_::LabelsHandler {
    using LongLabelsType = LongLabels;
    using ShortLabelsType = ShortLabels;
    using ArgLabelsType = ArgLabels;

    LabelsPolicy(): long_labels_{}, short_labels_{}, arg_labels_{} {
    }
    
    virtual void set_default_long(const std::string& name) {
        long_labels_.set_default(name);
    }
    virtual void set_long(const std::string& name, const std::string& label) {
        long_labels_.set(name, label);
    }
    virtual void set_long(const std::string& name, LabelIterator first_label, LabelIterator last_label) {
        long_labels_.set(name, first_label, last_label);
    }
    
    virtual void set_default_short(const std::string& name) {
        short_labels_.set_default(name);
    }
    virtual void set_short(const std::string& name, const std::string& label) {
        short_labels_.set(name, label);
    }
    virtual void set_short(const std::string& name, LabelIterator first_label, LabelIterator last_label) {
        short_labels_.set(name, first_label, last_label);
    }
    
    virtual void set_default_arg(const std::string& name) {
        arg_labels_.set_default(name);
    }
    virtual void set_arg(const std::string& name, const std::string& label) {
        arg_labels_.set(name, label);
    }

private:
    LongLabelsType  long_labels_;
    ShortLabelsType short_labels_;
    ArgLabelsType   arg_labels_;
};

using DefaultLabelsPolicy = LabelsPolicy<MultipleLongLabels, MultipleShortLabels, DefaultArgLabels>;

/** Description of Parameters of the program */
template <class HelpPolicy=DefaultHelpPolicy, class LabelsPolicy=DefaultLabelsPolicy>
class ParameterDescriptions {
public:
    ParameterDescriptions(): labels_{}, description_str_{}, epilog_str_{}, parameters_{} {
    }

    /** Set description string to display before the argument help */ 
    ParameterDescriptions& description(std::string description_str) {
        description_str_ = std::move(description_str);
        return *this;
    }
    
    /** Set the text to display after the argument help. */
    ParameterDescriptions& eiplog(std::string epilog_str) {
        epilog_str_ = std::move(epilog_str);
        return *this;
    }
    
    /** Set object whose arguments should also be included */
    ParameterDescriptions& add_parent(const ParameterDescriptions& parent) {
        return *this;
    }
    /** Set list of objects whose arguments should also be included */
    ParameterDescriptions& add_parents(std::initializer_list<std::reference_wrapper<const ParameterDescriptions>> parents) {
        return *this;
    }
    
    template <typename Type, class... Args>
    ParameterDescriptionBase& add_parameter(const std::string& name, const std::string& help_str) {
        using   ParameterType = ParameterDescription<Type, Args...>;
        return  *parameters_.insert(std::make_pair(name, std::move(make_unique_parameter<ParameterType>(labels_, name, help_str)))).first->second;
    }
    
    template <class Formatter=DefaultFormatter>
    std::ostream& print(std::ostream& os, Formatter formatter = Formatter{}) const {
        if (!description_str_.empty()) {
            formatter.print_description(os, description_str_);
        }
        os << std::endl;
        if (!epilog_str_.empty()) {
            formatter.print_description(os, epilog_str_);
        }
        return os;
    }
    
private:
    using ParameterMap = std::map<std::string, std::unique_ptr<ParameterDescriptionBase>>;
    
    template <typename Parameter, typename... Args>
    std::unique_ptr<ParameterDescriptionBase> make_unique_parameter(Args&&... args) {
        return std::unique_ptr<ParameterDescriptionBase>(new Parameter(std::forward<Args>(args)...));
    }
    
    LabelsPolicy    labels_;
    std::string     description_str_;
    std::string     epilog_str_;
    ParameterMap    parameters_;
};

template <class HelpPolicy, class LabelsPolicy>
inline std::ostream& operator<<(std::ostream& os, const ParameterDescriptions<HelpPolicy, LabelsPolicy>& pd) {
    return pd.print(os);
}

} // namespace program_parameters

#endif // PP_PARAMETER_DESCRIPTIONS_HPP