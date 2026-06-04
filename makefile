# Define the compiler
CXX = g++
CXXFLAGS = -std=c++20 -Wall

cooke_parser: lexer.cpp parser.cpp lexer.h parser.h
	$(CXX) $(CXXFLAGS) -o cooke_parser lexer.cpp parser.cpp
 
clean:
	rm -f cooke_parser
 
.PHONY: clean