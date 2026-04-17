CC = g++
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

main: main.cpp
	$(CC) main.cpp -o main.o $(LDFLAGS)