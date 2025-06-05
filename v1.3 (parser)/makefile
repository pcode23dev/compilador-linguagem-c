CC = gcc
CFLAGS = -Wall -Wextra -g -I./bin
OBJDIR = obj
BINDIR = bin
EXEC = $(BINDIR)/compilador

SRCS = main.c \
       src/analisador_lexico.c \
       src/analisador_sintatico.c

# Gerar caminhos para os .o dentro de obj/
OBJS = $(SRCS:.c=.o)
OBJS := $(patsubst %,$(OBJDIR)/%,$(OBJS))

# Substituir .c por .o, e adicionar pasta obj/
DEPS = $(OBJS:.o=.d)

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar .c em .o, salvando os .o em obj/
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJDIR) $(BINDIR)/compilador
