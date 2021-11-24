SRC=src
OBJ=obj
BIN=bin

CFLAGS += -W  -Wall -g3 -Iinclude -fsanitize=address
CC= gcc
TARGET= my_curl
RM= rm -rf

$(shell mkdir -p obj)

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) $(OBJ)/*.o 

fclean: clean
	$(RM) $(TARGET) $(OBJ)

re: 	fclean clean

.PHONY: all clean fclean re

