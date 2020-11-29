EXEC	=	observatory
OBJFILES	=	*.cpp

CC = g++
CFLAGS = -g -std=c++11 -Wall -pedantic -Wno-sign-conversion -Werror -lm
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
RUNCMD = ./$(EXEC) $$CAMERAS $$DIMENSIONS $(DEBUGFLAG)

.SILENT: all run clean valgrind dir observatory

ifneq ($(DEBUGFILE),)
  DEBUGFLAG := -d $(DEBUGFILE)
endif

all: $(EXEC)

run: dir all
	$(RUNCMD)
clean:
	rm -f img/* $(EXEC)

valgrind: all
	valgrind $(VFLAGS) $(RUNCMD)

dir:
	mkdir -p img

$(EXEC): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJFILES)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
