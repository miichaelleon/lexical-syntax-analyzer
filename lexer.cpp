// this program is a lexical analyzer for the Cooke programming language

#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>

#include "lexer.h"
#include "parser.h"

// global variables
int next_token;
int error_line = 1;
std::string token_name;
std::string lexeme;

// local variables
static int char_class;
static char next_char;
static FILE *infile;
static const std::unordered_map<std::string, std::pair<int, std::string>> TOKENS = {
    {":=", {ASSIGN_OP, "ASSIGN_OP"}},
    {"<", {LESSER_OP, "LESSER_OP"}},
    {">", {GREATER_OP, "GREATER_OP"}},
    {"=", {EQUAL_OP, "EQUAL_OP"}},
    {"<>", {NEQUAL_OP, "NEQUAL_OP"}},
    {"<=", {LEQUAL_OP, "LEQUAL_OP"}},
    {">=", {GEQUAL_OP, "GEQUAL_OP"}},
    {"(", {LEFT_PAREN, "LEFT_PAREN"}},
    {")", {RIGHT_PAREN, "RIGHT_PAREN"}},
    {"+", {ADD_OP, "ADD_OP"}},
    {"-", {SUB_OP, "SUB_OP"}},
    {"*", {MULT_OP, "MULT_OP"}},
    {"/", {DIV_OP, "DIV_OP"}},
    {"**", {POW_OP, "POW_OP"}},
    {"++", {INC_OP, "INC_OP"}},
    {"--", {DEC_OP, "DEC_OP"}},
    {";", {SEMICOLON, "SEMICOLON"}},
    {":", {COLON, "COLON"}},
    {"read", {KEY_READ, "KEY_READ"}},
    {"print", {KEY_PRINT, "KEY_PRINT"}},
    {"if", {KEY_IF, "KEY_IF"}},
    {"else", {KEY_ELSE, "KEY_ELSE"}},
    {"begin", {KEY_BEGIN, "KEY_BEGIN"}},
    {"end", {KEY_END, "KEY_END"}}
};

// local function declarations
static void add_char();
static void get_char();
static void get_non_blank();

// main function
int main(int argc, char* argv[]) {
    infile = fopen(argv[1], "r");

    if (argv[1] == NULL) {
        exit(2);
    }

    if (infile == NULL) {
        std::cout << "ERROR - cannot open file \n";
        exit(3);
    } else {
        // display R#
        std::cout << "Cooke Analyzer\n" << std::endl;
        get_char();
        // do {
            lex();
            program();
        // } while (next_token != EOF);
    }

    return 0;
}

// a function to lookup operators and parentheses and return the token 
static int lookup() {
    auto it = TOKENS.find(lexeme);

    if (it != TOKENS.end()) {
        next_token = it->second.first;
        token_name = it->second.second;
    }
    else {
        next_token = UNKNOWN;
        token_name = "UNKNOWN";
    }

    return next_token;
}

// a function to add next_char to lexeme
static void add_char() {
    lexeme += next_char;
}

// a function to get the next character of input and determine its character class
static void get_char() {
    if ((next_char = getc(infile)) != EOF) {
        if (isalpha(next_char))
            char_class = LETTER;
        else if (isdigit(next_char))
            char_class = DIGIT;
        else
            char_class = CHAR;
    } else {
        char_class = EOF;
    }
}

// a function to call get_char until it returns a non-whitespace character
static void get_non_blank() {
    while (isspace(next_char)) {
        if (next_char == '\n') {
            error_line++;
        }
        get_char();
    
    }
}

// a lexical analyzer
int lex() {
    lexeme = "";
    get_non_blank();

    switch (char_class) {
        // parse identifiers
        case LETTER:
            add_char();
            get_char();
            while (char_class == LETTER || char_class == DIGIT) {
                add_char();
                get_char();
            }

            lookup();

            if (next_token != KEY_READ && next_token != KEY_PRINT && next_token != KEY_IF &&
                next_token != KEY_END && next_token != KEY_ELSE && next_token != KEY_BEGIN) {
                    next_token = IDENT;
                    token_name = "IDENT";
                }
                
            break;

        // parse integer literals
        case DIGIT:
            add_char();
            get_char();
            while (char_class == DIGIT) {
                add_char();
                get_char();
            }
            next_token = INT_LIT;
            token_name = "INT_LIT";
            break;

        // non alphabetical or numeric characters
        case CHAR:
            add_char();
            get_char();

            if (lexeme == ":" && next_char == '=') {
                add_char();
                get_char();
            }
            else if (lexeme == "<" && next_char == '>') {
                add_char();
                get_char();
            }
            else if (lexeme == "<" && next_char == '=') {
                add_char();
                get_char();
            }
            else if (lexeme == ">" && next_char == '=') {
                add_char();
                get_char();
            }
            else if (lexeme == "*" && next_char == '*') {
                add_char();
                get_char();
            }
            else if (lexeme == "+" && next_char == '+') {
                add_char();
                get_char();
            }
            else if (lexeme == "-" && next_char == '-') {
                add_char();
                get_char();
            }
            
            lookup();
            break;

        // EOF
        case EOF:
            next_token = EOF;
            lexeme += "EOF";
            break;
    }

    if (lexeme != "EOF") {
        std::cout << lexeme << "\t" << token_name << std::endl;
    }
    return next_token;
}