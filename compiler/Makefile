fisrt: compiler

compiler: constants.o lexical.o semantic.o syntactic.o
	ar rcs libcompiler.a debug/Constants.o debug/Lexical.o debug/Semantic.o debug/Syntactic.o

constants.o: Constants.cpp
	g++ -c Constants.cpp -o debug/Constants.o

lexical.o: Lexical.cpp
	g++ -c Lexical.cpp -o debug/Lexical.o

semantic.o: Semantic.cpp
	g++ -c Semantic.cpp -o debug/Semantic.o

syntactic.o: Syntactic.cpp
	g++ -c Syntactic.cpp -o debug/Syntactic.o