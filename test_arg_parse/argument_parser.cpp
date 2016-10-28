#include "argument_parser.hpp"

namespace argparse {


ArgumentParser::ArgumentParser(): prog_{}
{
    //ctor
}

ArgumentParser& ArgumentParser::prog(std::string prog_name) {
    prog_ = std::move(prog_name);
    return *this;
}

ArgumentParser& ArgumentParser::usage(std::string usage_message) {
    usage_ = std::move(usage_message);
    return *this;
}

}
