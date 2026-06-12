#ifndef LEXER_H
#define LEXER_H

// character classes
#define LETTER 0    // alphabetical character
#define DIGIT 1    // numeric character
#define CHAR 2    // non alphabetical or numeric character

// tokens
#define ASSIGN_OP 10
#define LESSER_OP 11
#define GREATER_OP 12
#define EQUAL_OP 13
#define NEQUAL_OP 14
#define LEQUAL_OP 15
#define GEQUAL_OP 16
#define LEFT_PAREN 17
#define RIGHT_PAREN 18

#define ADD_OP 20
#define SUB_OP 21
#define MULT_OP 22
#define DIV_OP 23
#define POW_OP 24
#define INC_OP 25
#define DEC_OP 26
#define SEMICOLON 27
#define COLON 28

#define KEY_READ 30
#define KEY_PRINT 31
#define KEY_IF 32
#define KEY_ELSE 33
#define KEY_BEGIN 34
#define KEY_END 35
#define IDENT 36
#define INT_LIT 37

#define UNKNOWN 99


int lex(std::ifstream& infile);

#endif
