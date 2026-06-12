#ifndef PARSER_H
#define PARSER_H

void program(std::ifstream& infile);

extern int next_token;
extern std::string lexeme;
extern std::string token_name;
extern int error_line;
#endif
