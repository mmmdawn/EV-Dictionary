# change application name here (executable output name)
TARGET=dictionary

defaut: run
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
 
PTHREAD=-pthread 
 
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe
 
CXX_FLAGS = -no-pie -fexceptions -std=c++11 -Wno-deprecated-declarations -Wno-reorder -lpthread -ldl
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
 
# linker
LD=gcc
LDFLAGS= $(PTHREAD) $(GTKLIB) libsqlite.a -export-dynamic
 
OBJS=main.o
 
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS) ${CXX_FLAGS}
    
main.o: main.c
	$(CC) -c $(CCFLAGS) main.c $(GTKLIB) -o main.o

run: all $(OBJS)
	./dictionary

clean:
	rm -f *.o $(TARGET)
