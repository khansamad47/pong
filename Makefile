build:
	g++ -o pong main.cpp pong_game.cpp -lSDL2

format:
	clang-format -i *.h *.cpp
