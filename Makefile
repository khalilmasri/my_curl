SRC=src
OBJ=obj
BIN=bin

CFLAGS += -W  -Wall -g3 -Iinclude 
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
	$(RM) $(TARGET) $(BIN)/*.dSYM $(OBJ)
