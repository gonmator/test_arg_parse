#pragma once
#ifndef TESTS_HPP_INCLUDED
#define TESTS_HPP_INCLUDED

#include <cassert>
#include <locale>
#include <string>
#include <vector>

const std::string descr = "Test help description. It contains 123456790 12345267890 1234567890 12334567890 1234567890 1234567890 "
    "1234567890 1234567890 characters.";
const std::string helpOpt = "help";
const std::string usageOpt = "usage";
const std::string strOpt = "string";
const std::string intOpt = "integer";
const std::string flagOpt = "flag";
const std::string strVecOpt = "strings";
const std::string intVecOpt = "integers";
const std::string pos_0 = "pos_0";
const std::string pos_N = "pos_N";

inline std::string shortOpt(const std::string& logOpt) {
    assert(!logOpt.empty());
    
    return std::string(1, std::use_facet<std::ctype<char>>(std::locale{}).toupper(logOpt[0]));
}

inline std::string longPrefixedOpt(const std::string& longOpt) {
    return std::string{"--"}.append(longOpt);
}

inline std::string shortPrefixedOpt(const std::string& shortOpt) {
    return std::string{"-"}.append(shortOpt);
}

inline std::string optHelp(const std::string opt) {
    return std::string{"This is the help message related to the "}.append(opt).append(" option.");
}

inline std::string makeNameValue(const std::string& longOpt) {
    std::string rv(longOpt);
    std::use_facet<std::ctype<char>>(std::locale{}).toupper(&rv[0], &rv[rv.size()]);
    return rv;
}

struct Options {
    Options() = default;
    Options(const Options&) = default;
    Options& operator=(const Options&) = default;
    
    std::string                 str_value;
    int                         int_value;
    bool                        flag;
    std::vector<std::string>    str_vector_value;
    std::vector<int>            int_vector_value;
    std::string                 pos_0;
    std::vector<std::string>    pos_N;
};

Options test_program_options(int argc, char* argv[]);

void test_hello_world(int argc, char* argv[]);

#endif // TESTS_HPP_INCLUDED
