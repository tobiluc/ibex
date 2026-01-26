#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

namespace ibex
{

///==================
/// Tokens
///==================

struct Token
{

    enum class Type : unsigned char
    {
        UNKNOWN,
        INT, FLOAT, IDENTIFIER,
        COMMA, LPAREN, RPAREN,
        PLUS, MINUS, TIMES, DIV, POW,
        UNARY_PLUS, UNARY_MINUS,
        LOR, LAND, NOT,
        EQ, NEQ, LEQ, GEQ, LESS, GREATER
    };

    Token::Type type = Type::UNKNOWN;
    std::string lexeme = "";
    u_int64_t metadata = 0;

    inline bool operator==(const Token& t) const {
        return type == t.type && lexeme == t.lexeme && metadata == t.metadata;
    }
};

std::ostream& operator<<(std::ostream& os, const Token& token);

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
///  Postfix
///==================

std::vector<Token> generate_postfix(const std::vector<Token>& tokens);

///==================
/// Evaluation
///==================

double evaluate(const std::vector<Token>& postfix, const Variables& vars, const Functions& funcs);

double evaluate(const char* text);

}
