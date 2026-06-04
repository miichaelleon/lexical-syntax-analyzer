#include <iostream>

#include "parser.h"
#include "lexer.h"

static void error();

void program() {
    statement();
}

void statement() {
    if (next_token == IDENT) {
        lex();
        if(next_token == ASSIGN_OP)  {
            lex();
            expression(); //1
            statement_not();
        } else {
            error();
        }
    } else if (next_token == KEY_READ) {
        lex();
        if (next_token == LEFT_PAREN) {
            lex();
            expression();
            if (next_token == RIGHT_PAREN) {
                lex();
                statement_not();
            } else {
                error();
            }
        } else {
            error();
        }
    } else if (next_token == INC_OP || next_token == DEC_OP) {
        operation();
        statement_not();
    } else if (next_token == KEY_READ) {
        lex();
        if (next_token == LEFT_PAREN) {
            lex();
            if (next_token == IDENT) {
                lex();
                if (next_token == RIGHT_PAREN) {
                    lex();
                    statement_not();
                } else {
                    error();
                }
            } else {
                error();
            }
        } else {
            error();
        }
    } else if (next_token == KEY_PRINT) {
        lex();
        if (next_token == LEFT_PAREN) {
            lex();
            expression();
            if (next_token == RIGHT_PAREN) {
                lex();
                statement_not();
            } else {
                error();
            }
        } else {
            error();
        }
    } else if (next_token == KEY_IF) {
        lex();
        condition();
        if (next_token == COLON) {
            lex();
            if (next_token == KEY_BEGIN) {
                lex();
                statement();
                if (next_token == KEY_END) {
                    lex();
                    statement_not();
                } else if (next_token == KEY_ELSE) {
                    lex();
                    if (next_token == COLON) {
                        lex();
                        statement();
                        if (next_token == KEY_END) {
                            lex();
                            statement_not();
                        } else {
                            error();
                        }
                    } else {
                        error();
                    }
                } else {
                    error();
                }
            } else {
                error();
            }
        } else {
            error();
        }
    }
    else {
        error();
    }
}

void statement_not() {
    if (next_token == SEMICOLON) {
        lex();
        statement();
        statement_not();
    } else if (next_token == EOF) {
        std::cout << "Syntax Validated." << std::endl;
        exit(0);
    }
}

void condition() {
    expression();

    if (next_token == LESSER_OP ||next_token == GREATER_OP || next_token == EQUAL_OP ||
        next_token == NEQUAL_OP|| next_token == LEQUAL_OP  || next_token == GEQUAL_OP) {
        lex();
        expression();
    }
}

void expression() {
    term(); //1

    while (next_token == ADD_OP || next_token == SUB_OP) {
        lex();
        term();
    }
} 

void term() {
    factor(); //2

    while (next_token == MULT_OP || next_token == DIV_OP || next_token == POW_OP) {
            lex();
            factor();
    }

}

void factor() {
    if (next_token == IDENT || next_token == INT_LIT) {
        lex();
    } else {
        if (next_token == LEFT_PAREN) {
            lex(); 
            expression(); //3

            if (next_token == RIGHT_PAREN) {
                lex(); 
            } else { 
                error();
            }
        } else { 
            error(); 
        }
    }
} 

void operation() {
    if (next_token == INC_OP || next_token == DEC_OP) {
        lex();
        if (next_token == IDENT) {
            lex();
        } else {
            error();
        }
    }
}

static void error() {
    std::cout << "Error encounter on line " << error_line << ": ";
    std::cout << "The next lexeme was " << lexeme << " ";
    std::cout << "and the next token was " << token_name << std::endl;
    exit(1);
}