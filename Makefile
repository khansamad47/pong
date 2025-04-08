format:
	clang-format -i src/*.h src/*.cpp

tidy:
	clang-tidy -p build src/*
