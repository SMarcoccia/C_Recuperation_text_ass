
CC = gcc
CFLAG = -O3 -g -Wall -Werror -Wextra -DDEBUG
CCCOM = $(CC) $(CFLAG) -std=c11
LDLIBS = -lmingw32 -lws2_32
LDFLAGS = -L/mingw/lib
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
RM = del -f
EXEC = recupTxt

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CCCOM) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: clean

clean:
	$(RM) *.o *~ *.stackdump *.bak *.exe 

