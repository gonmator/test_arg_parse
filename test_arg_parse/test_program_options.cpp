#include <exception>
#include <iostream>
#include <string>

#include <boost/program_options/errors.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>

#include "tests.hpp"

namespace po = boost::program_options;

inline std::string makeOptionName(const std::string& longOpt) {
    return (longOpt + "," + shortOpt(longOpt));
}

Options test_program_options(int argc, char* argv[]) {
    Options options{};

    po::options_description desc{descr};
    desc.add_options()
        (makeOptionName(helpOpt).c_str(), 
            optHelp(helpOpt).c_str())
        (makeOptionName(strOpt).c_str(), po::value<std::string>(&options.str_value)->value_name(makeNameValue(strOpt)), 
            optHelp(strOpt).c_str())
        (makeOptionName(intOpt).c_str(), po::value<int>(&options.int_value)->value_name(makeNameValue(intOpt)), 
            optHelp(intOpt).c_str())
        (std::string(",").append(shortOpt(flagOpt)).c_str(), po::bool_switch(&options.flag), 
            optHelp(flagOpt).c_str())
        (strVecOpt.c_str(), po::value<std::vector<std::string>>(&options.str_vector_value)->multitoken()->value_name(makeNameValue(strVecOpt)), 
            optHelp(strVecOpt).c_str())
        (intVecOpt.c_str(), po::value<std::vector<int>>(&options.int_vector_value)->multitoken()->value_name(makeNameValue(intVecOpt)), 
            optHelp(intVecOpt).c_str())
        (pos_0.c_str(), po::value<std::string>(&options.pos_0)->required(), 
            optHelp(pos_0).c_str())
        (pos_N.c_str(), po::value<std::vector<std::string>>(&options.pos_N),
            optHelp(pos_N).c_str())
        ;

    po::positional_options_description  pd;
    pd.add(pos_0.c_str(), 1).add(pos_N.c_str(), -1);
    
    po::variables_map   vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pd).run(), vm);
        std::cout << "JJEEEJJEE";
        po::notify(vm);
    } catch (const po::error& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << desc << std::endl;
        exit(1);
    }
    
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        exit(0);
    }
    
    return options;
}
