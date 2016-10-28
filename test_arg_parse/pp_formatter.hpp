#ifndef PP_FORMATTER_HPP
#define PP_FORMATTER_HPP
#pragma once

#include <algorithm>
#include <iostream>
#include <locale>
#include <string>
#include <ostream>

namespace program_parameters {

struct DefaultFormatter {
    std::ostream& print_description(std::ostream& os, const std::string& description) const {
        if (os == std::cout) {
            print_width_care(os, description);
        } else {
            print_no_care(os, description);
        }
        return os;
    }

private:
    class TokenIterator {
        using reference = std::string;
        using value_type = std::string;
    public:
        TokenIterator() = default;
        TokenIterator(const TokenIterator&) = default;
        TokenIterator& operator=(const TokenIterator&) = default;
        TokenIterator(TokenIterator&&) = default;
        TokenIterator& operator=(TokenIterator&&) = default;
        
        TokenIterator(const std::string& str): current_{str.cbegin()}, end_{str.cend()} {
            calc_token();
        }
        const std::string operator*() const {
            return std::string{current_, next_};
        }
        TokenIterator& operator++() {
            current_ = next_;
            calc_token();
            return *this;
        }
        TokenIterator operator++(int) {
            TokenIterator   rv{*this};
            operator++();
            return rv;
        }
        bool operator==(const TokenIterator& rhs) const {
            return (current_ == rhs.current_ && end_ == rhs.end_) || (current_ == end_ && rhs.current_ == rhs.end_);
        }
        bool operator!=(const TokenIterator& rhs) const {
            return !(*this == rhs);
        }
    private:
        using StringIt = std::string::const_iterator;
        
        void calc_token() {
            auto is_space = [](char c){ return std::isspace(c, std::locale()); };
            next_ = std::find_if_not(std::find_if(current_, end_, is_space), end_, is_space);
        }
        
        StringIt    current_;
        StringIt    next_;
        StringIt    end_;
    };
    
    void print_width_care(std::ostream& os, std::string str) const {
        TokenIterator   it{str};
        TokenIterator   endIt;
        unsigned int    pos = 0;
        while (it != endIt) {
            auto    token = *it++;
            if (pos > 0 && pos + token.size() >= width_) {
                os << std::endl;
                pos = 0;
            }
            os << token;
            pos += token.size();
        }
        os << std::endl;
    }
    
    static void print_no_care(std::ostream& os, std::string str) {
        os << str << std::endl << std::endl;
    }

    unsigned int    width_ = 80;
};    

} // namespace program_parameters


#endif // PP_FORMATTER_HPP