OBJECTS = src/main.o src/server.o src/kolua.o
FLAGS = -lpthread -lnanomsg -Wall -Wextra -pedantic -g -llua -ldl -I/usr/local/include/ -L/usr/local/lib
BINARY = hackuser-server

build: $(OBJECTS)
	gcc -o $(BINARY) $(OBJECTS) $(FLAGS)
	
run: build
	./$(BINARY)
	
%.o: %.cpp
	g++ -o $@ -c $< $(FLAGS)
	
%.o: %.c
	gcc -o $@ -c $< $(FLAGS)

clean:
	rm **/*.o
