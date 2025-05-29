CC = gcc
CFLAGS = -Wall -Wextra -g -I./bin
OBJDIR = src
BINDIR = bin
EXEC = compilador

SRCS = main.c \
       src/analisador_lexico.c \
       src/analisador_sintatico.c

OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(EXEC)