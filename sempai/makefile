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
 
CMAKE_CXX_FLAGS = -no-pie -fexceptions -std=c++11 -Wno-deprecated-declarations -Wno-reorder
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
 
# linker
LD=gcc
LDFLAGS= $(PTHREAD) $(GTKLIB) src/bt-5.0.0/lib/libbt.a -export-dynamic
 
OBJS=main.o
 
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS) ${CMAKE_CXX_FLAGS}
    
main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) -o main.o

run: all $(OBJS)
	./dictionary

clean:
	rm -f *.o $(TARGET)
