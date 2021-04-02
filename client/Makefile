OBJECTS = src/main.o src/logging.o src/client.o src/buffers.o
FLAGS = -lpthread-lncurses -Wall -Wextra -pedantic -g
BINARY = hackuser

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
