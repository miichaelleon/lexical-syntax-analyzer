#ifndef PARSER_H
#define PARSER_H

void program();

void statement();
void statement_not();
void condition();
void expression();
void term();
void term_not();
void factor();
void operation();

extern int next_token;
extern std::string lexeme;
extern std::string token_name;
extern int error_line;
#endif
