#include <iostream>

#include "tests.hpp"

#include <tclap/CmdLine.h>

Options test_program_options(int argc, char* argv[]) {
    Options options{};
    
    try {
        TCLAP::CmdLine  cmd{descr};
        
        TCLAP::ValueArg<std::string>    strArg(shortOpt(strOpt), strOpt, optHelp(strOpt), false, "", makeNameValue(strOpt));
        cmd.add(strArg);
        TCLAP::ValueArg<int>    intArg(shortOpt(intOpt), intOpt, optHelp(intOpt), false, 0, makeNameValue(intOpt));
        cmd.add(intArg);
        TCLAP::SwitchArg    flagArg(shortOpt(flagOpt), "", optHelp(flagOpt));
        cmd.add(flagArg);
        TCLAP::MultiArg<std::string>    strVecArg("", strVecOpt, optHelp(strVecOpt), false, makeNameValue(strVecOpt));
        cmd.add(strVecArg);
        TCLAP::MultiArg<int>    intVecArg("", intVecOpt, optHelp(intVecOpt), false, makeNameValue(intVecOpt));
        cmd.add(intVecArg);
        TCLAP::UnlabeledValueArg<std::string>   pos_0Arg(pos_0, optHelp(pos_0), true, "", makeNameValue(pos_0));
        cmd.add(pos_0Arg);
        TCLAP::UnlabeledMultiArg<std::string>   pos_NArg(pos_N, optHelp(pos_N), false, makeNameValue(pos_0));
        cmd.add(pos_NArg);
        
        cmd.parse(argc, argv);
        options.str_value = strArg.getValue();
        options.int_value = intArg.getValue();
        options.flag = flagArg.getValue();
        options.str_vector_value = strVecArg.getValue();
        options.int_vector_value = intVecArg.getValue();
        options.pos_0 = pos_0Arg.getValue();
        options.pos_N = pos_NArg.getValue();
        
    } catch (const TCLAP::ArgException& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return options;
}
