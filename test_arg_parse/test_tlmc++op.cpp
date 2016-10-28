#include <iostream>

#include <optionparser.h>

#include "tests.hpp"

namespace o = option;
Options test_program_options(int argc, char* argv[]) {
    enum OptionIndex {
        HELP, STR, INT, FLAG, STR_VEC, INT_VEC, POS_0, POS_N
    };
    enum OptionType {
        ANY
    };
    const o::Descriptor usage[] = {
        {HELP, ANY, shortOpt(helpOpt).c_str(), helpOpt.c_str(), o::Arg::None, optHelp(helpOpt).c_str()},
        {STR, ANY, shortOpt(strOpt).c_str(), strOpt.c_str(), o::Arg::Optional, optHelp(strOpt).c_str()},
        {INT, ANY, shortOpt(intOpt).c_str(), intOpt.c_str(), o::Arg::Optional, optHelp(intOpt).c_str()},
        {FLAG, ANY, shortOpt(flagOpt).c_str(), "", o::Arg::None, optHelp(flagOpt).c_str()},
        {STR_VEC, ANY, "", strVecOpt.c_str(), o::Arg::Optional, optHelp(strVecOpt).c_str()},
        {INT_VEC, ANY, "", intVecOpt.c_str(), o::Arg::Optional, optHelp(intVecOpt).c_str()}
    };
    
    argc-=(argc>0); 
    argv+=(argc>0);
    
    Options options{};

    o::Stats    stats(usage, argc, argv);
    o::Option   opt[stats.options_max], buffer[stats.buffer_max];
    o::Parser   parse(usage, argc, argv, opt, buffer);
    
    if (parse.error()) {
        exit(1);
    }
    if (opt[HELP] || argc == 0) {
        o::printUsage(std::cout, usage);
        exit(0);
    }
    
    return options;
}
