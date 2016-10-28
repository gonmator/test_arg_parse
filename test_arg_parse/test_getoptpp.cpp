#include "tests.hpp"

#include <algorithm>
#include <iostream>

#include <getoptpp/getopt_pp_standalone.h>

namespace go = GetOpt;

Options test_program_options(int argc, char* argv[]) {
    Options options{};

    go::GetOpt_pp   opt_man(argc, argv);
    
    if (opt_man >> go::OptionPresent(shortOpt(helpOpt)[0], helpOpt)) {
        std::cout << "Help! Ayúdame!" << std::endl;
        exit(0);
    }
    
    std::vector<std::string>    poss;
    
    opt_man >> 
        go::Option(shortOpt(strOpt)[0], strOpt, options.str_value) >>
        go::Option(shortOpt(intOpt)[0], intOpt, options.int_value) >>
        go::Option(strVecOpt, options.str_vector_value) >>
        go::Option(intVecOpt, options.int_vector_value) >>
        go::GlobalOption(poss);
    auto    b = poss.cbegin();
    auto    e = poss.cend();
    if (b != e) {
        options.pos_0 = *b++;
        options.pos_N.insert(options.pos_N.end(), b, e);
    }
    
    return options;
}
