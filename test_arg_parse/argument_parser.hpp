#pragma once
#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <string>

#include "formatter_class.hpp"

namespace argparse {

template <class FormatterClass=DefaultFormatterClass>
class ArgumentParser
{
    public:
        /** Default constructor */
        ArgumentParser();
        /** Name of the program */
        ArgumentParser& prog(std::string prog_name);
        /** Usage message */
        ArgumentParser& usage(std::string usage_message);
        /** Description */
        ArgumentParser& description(std::string description_message);
        /** Epilog message */
        ArgumentParser& epilog(std::string epilog_message);
        /** Parent arguments */
        ArgumentParser& parent(const ArgumentParser& parent_parse);
        /** Prefix characters */
        ArgumentParser& prefixChars(std::string prefix_chars);
        /** Char to read from file parameters */
        ArgumentParser& fromFilePrefixChars(std::string prefix_chars);
    protected:
    private:
        std::string prog_;
        std::string usage_;
        std::string description_;
        std::string epilog_;
        std::string prefix_chars;
        std::string from_file_prefix_chars;
};

} // namespace argparse

#endif // ARGUMENT_PARSER_H
