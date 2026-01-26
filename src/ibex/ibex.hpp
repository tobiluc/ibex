#pragma once

#include <iostream>
#include <vector>
#include <cctype>
#include <string>

namespace ibex
{

///==================
/// Tokens
///==================

struct Token
{

    enum class Type : unsigned char
    {
        UNKNOWN, END,
        INT, FLOAT, IDENTIFIER,
        COMMA, LPAREN, RPAREN,
        PLUS, MINUS, TIMES, DIV, POW,
        UNARY_PLUS, UNARY_MINUS,
        LOR, LAND, NOT,
        EQ, NEQ, LEQ, GEQ, LESS, GREATER
    };

    Token::Type type;
    std::string lexeme;
    u_int64_t metadata = 0;

    static const Token UNKNOWN;
    static const Token END;
};

inline std::ostream& operator<<(std::ostream& os, const Token& token)
{
    os << "Token(" << (int)(token.type) << ", \"" << token.lexeme << "\", " << token.metadata  <<")";
    return os;
}

std::vector<Token> tokenize(const char* text);

///==================
/// Functions
///==================
using Variables = std::unordered_map<std::string, double>;
using FunctionArgs = std::vector<double>;
using FunctionImpl = std::function<double(const FunctionArgs&)>;
using Functions = std::unordered_map<std::string, FunctionImpl>;

void register_commons(Variables& vars, Functions& funcs);

///==================
/// Reverse Polish
///==================

struct RPN
{
    std::vector<Token> tokens;
};

RPN generate_reverse_polish(const std::vector<Token>& tokens);

///==================
/// Evaluation
///==================

double evaluate(const RPN& rpn, const Variables& vars, const Functions& funcs);

double evaluate(const char* text);

}
