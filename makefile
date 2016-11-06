CC=g++ -g -std=c++11
BAKEFLAGS=
CFLAGS=-c -Wall -I ./headers
OBJDIR=obj/
SRCDIR=src/
HDIR=headers/
NAME=k3.2

$(OBJDIR)main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -pthread -o $(OBJDIR)main.o $(BAKEFLAGS)

all: $(OBJDIR)main.o
const:
	make all --no-print-directory
	$(CC) obj/*.o -o $(NAME) -pthread $(BAKEFLAGS)
	ctags -R --languages=C,C++ --c++-kinds=+p --fields=+iaS --extra=+q ./
clean:
	rm -d -r $(OBJDIR)* *.o $(NAME)
