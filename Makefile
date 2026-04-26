CC = g++
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CXXFLAGS = -std=c++23 -Wall -Wextra

main: main.cpp
	$(CC) $(CXXFLAGS) main.cpp -o main.o $(LDFLAGS)