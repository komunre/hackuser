OBJECTS = src/main.o src/server.o src/kolua.o src/lua_funcs.o src/db.c
FLAGS = -lpthread -Wall -Wextra -pedantic -g -llua -ldl -lm -I/usr/local/include/hiredis -lhiredis
INCLUDE=-I../lib/lua-5.4.6/install/include -L../lib/lua-5.4.6/install/lib -I../lib/hiredis-1.2.0/ -L../lib/hiredis-1.2.0/install
BINARY = hackuser-server

build: $(OBJECTS)
	gcc -o $(BINARY) $(OBJECTS) $(INCLUDE) $(FLAGS)
	
run: build
	./$(BINARY)
	
%.o: %.cpp
	g++ -o $@ -c $< $(INCLUDE) $(FLAGS)
	
%.o: %.c
	gcc -o $@ -c $< $(INCLUDE) $(FLAGS)

clear:
	rm **/*.o
