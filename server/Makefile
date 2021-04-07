OBJECTS = src/main.o src/server.o src/kolua.o src/lua_funcs.o src/db.c
FLAGS = -lpthread -Wall -Wextra -pedantic -g -llua -ldl -lm -I/usr/local/include/hiredis -lhiredis
BINARY = hackuser-server

build: $(OBJECTS)
	gcc -o $(BINARY) $(OBJECTS) $(FLAGS)
	
run: build
	./$(BINARY)
	
%.o: %.cpp
	g++ -o $@ -c $< $(FLAGS)
	
%.o: %.c
	gcc -o $@ -c $< $(FLAGS)

clear:
	rm **/*.o
