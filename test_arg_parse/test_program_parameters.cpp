#include <iostream>

#include "pp_parameter_descriptions.hpp"

#include "tests.hpp"

namespace po = program_parameters;

template <class Parameter>
void showParameter(const std::string& name, const Parameter& p) {
    std::cout << name << ": ";
    std::cout << p.min_arguments() << ", " << p.max_arguments() <<", " << std::boolalpha << p.required() << ", " << p.unique() << std::endl;
}

Options test_program_options(int argc, char* argv[]) {
    Options rv{};

    po::ParameterDescriptions<> pd;
    pd.description(descr);
    pd.add_parameter<std::string>(strOpt, optHelp(strOpt)).short_label();
    pd.add_parameter<int>(intOpt, optHelp(intOpt)).short_label();
    pd.add_parameter<bool>(flagOpt, optHelp(flagOpt)).short_label().long_label({"flag", "glag"});
    
    std::cout << pd << std::endl;
    
/*    auto    helpDescr = po::FlagOptionDescription{helpOpt, optHelp(helpOpt)};
    auto    usageDescr = po::FlagOptionDescription{usageOpt, optHelp(usageOpt)};
    po::UniqueOptionDescription<std::string>    strDescr(strOpt, optHelp(strOpt));
    po::UniqueOptionDescription<std::string>    intDescr(intOpt, optHelp(intOpt));
    po::FlagOptionDescription                   flagDescr(flagOpt, optHelp(flagOpt));
    po::MultiOptionDescription<std::string>     strVecDescr(strVecOpt, optHelp(strVecOpt));
    po::MultiOptionDescription<int>             intVecDescr(intVecOpt, optHelp(intVecOpt));

    po::Syntax  syntax;
    syntax
        .new_flag_option(helpOpt, optHelp(helpOpt))
        .new_flag_option(usageOpt, optHelp(usageOpt))
        .new_unique_option<std::string>(strOpt, optHelp(strOpt))
        .new_unique_option<int>(intOpt, optHelp(intOpt))
        .new_flag_option(flagOpt, optHelp(flagOpt))
        .new_multi_option<std::string>(strVecOpt, optHelp(strVecOpt))
        .new_multi_option<int>(intVecOpt, optHelp(intVecOpt))
        ;*/
        
   
    return rv;
}
