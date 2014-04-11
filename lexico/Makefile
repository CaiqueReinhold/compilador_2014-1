
all: lexico

lexico: constants.o lexical.o
	ar rcs liblexico.a debug/Constants.o debug/Lexical.o

constants.o: Constants.cpp
	g++ -c Constants.cpp -o debug/Constants.o

lexical.o: Lexical.cpp
	g++ -c Lexical.cpp -o debug/Lexical.o