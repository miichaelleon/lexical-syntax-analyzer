#include <iostream>

#include "parser.h"
#include "lexer.h"

static void statement(std::ifstream& infile);
static void statement_not(std::ifstream& infile);
static void condition(std::ifstream& infile);
static void expression(std::ifstream& infile);
static void term(std::ifstream& infile);
static void factor(std::ifstream& infile);
static void operation(std::ifstream& infile);

static void error();

void program(std::ifstream& infile) {
    statement(infile);
}

static void statement(std::ifstream& infile) {
    if (next_token == IDENT) {
        lex(infile);
        if(next_token == ASSIGN_OP)  {
            lex(infile);
            expression(infile); //1
            statement_not(infile);
        } else {
            error();
        }
    } else if (next_token == KEY_READ) {
        lex(infile);
        if (next_token == LEFT_PAREN) {
            lex(infile);
            expression(infile);
            if (next_token == RIGHT_PAREN) {
                lex(infile);
                statement_not(infile);
            } else {
                error();
            }
        } else {
            error();
        }
    } else if (next_token == INC_OP || next_token == DEC_OP) {
        operation(infile);
        statement_not(infile);
    } else if (next_token == KEY_READ) {
        lex(infile);
        if (next_token == LEFT_PAREN) {
            lex(infile);
            if (next_token == IDENT) {
                lex(infile);
                if (next_token == RIGHT_PAREN) {
                    lex(infile);
                    statement_not(infile);
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
        lex(infile);
        if (next_token == LEFT_PAREN) {
            lex(infile);
            expression(infile);
            if (next_token == RIGHT_PAREN) {
                lex(infile);
                statement_not(infile);
            } else {
                error();
            }
        } else {
            error();
        }
    } else if (next_token == KEY_IF) {
        lex(infile);
        condition(infile);
        if (next_token == COLON) {
            lex(infile);
            if (next_token == KEY_BEGIN) {
                lex(infile);
                statement(infile);
                if (next_token == KEY_END) {
                    lex(infile);
                    statement_not(infile);
                } else if (next_token == KEY_ELSE) {
                    lex(infile);
                    if (next_token == COLON) {
                        lex(infile);
                        statement(infile);
                        if (next_token == KEY_END) {
                            lex(infile);
                            statement_not(infile);
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

static void statement_not(std::ifstream& infile) {
    if (next_token == SEMICOLON) {
        lex(infile);
        statement(infile);
        statement_not(infile);
    } else if (next_token == EOF) {
        std::cout << "Syntax Validated." << std::endl;
        exit(0);
    }
}

static void condition(std::ifstream& infile) {
    expression(infile);

    if (next_token == LESSER_OP ||next_token == GREATER_OP || next_token == EQUAL_OP ||
        next_token == NEQUAL_OP|| next_token == LEQUAL_OP  || next_token == GEQUAL_OP) {
        lex(infile);
        expression(infile);
    }
}

static void expression(std::ifstream& infile) {
    term(infile); //1

    while (next_token == ADD_OP || next_token == SUB_OP) {
        lex(infile);
        term(infile);
    }
} 

static void term(std::ifstream& infile) {
    factor(infile); //2

    while (next_token == MULT_OP || next_token == DIV_OP || next_token == POW_OP) {
            lex(infile);
            factor(infile);
    }

}

static void factor(std::ifstream& infile) {
    if (next_token == IDENT || next_token == INT_LIT) {
        lex(infile);
    } else {
        if (next_token == LEFT_PAREN) {
            lex(infile); 
            expression(infile); //3

            if (next_token == RIGHT_PAREN) {
                lex(infile); 
            } else { 
                error();
            }
        } else { 
            error(); 
        }
    }
} 

static void operation(std::ifstream& infile) {
    if (next_token == INC_OP || next_token == DEC_OP) {
        lex(infile);
        if (next_token == IDENT) {
            lex(infile);
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