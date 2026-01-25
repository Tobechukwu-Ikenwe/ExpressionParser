CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = src/main.c src/lexer.c src/parser.c src/ast.c src/eval.c
OBJ = $(SRC:.c=.o)
TARGET = expression-parser

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
.PHONY: all clean
