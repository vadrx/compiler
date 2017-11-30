all:
	g++ -std=c++11 main.cpp lex.cpp pars.cpp -o main && ./main