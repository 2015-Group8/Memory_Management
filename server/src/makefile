#########################################
#
#		b.s. kim
#
#########################################
CCC_SOL		= cc
CCC_SOL64	= /appl/SOL/SUNWspro6/bin/CC
CCC_LINUX	= gcc
CCC_LINUX64	= gcc

CC= $(CCC_LINUX)
OBJS= main.o my_list.o util.o

#CFLAGS= -DENABLE_DLOG_OUT -c 
CFLAGS= -c 
OFLAGS= -o

EXTLIBS	= `pkg-config --libs glib-2.0`

ALL : main

main: $(OBJS)  
	$(CC) $(OFLAGS) test $(OBJS) $(EXTLIBS) -lsqlite3 -lm

main.o: main.c
	$(CC) $(CFLAGS) `pkg-config --cflags glib-2.0`  main.c

util.o: util.c util.h
	$(CC) $(CFLAGS) util.c

my_list.o: my_list.c my_list.h
	$(CC) $(CFLAGS) my_list.c

clean :
	rm -f test *.o core *~
