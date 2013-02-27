SRC = ./src
BUILD = ./build
INC = ./inc

OBJS = build/llist.o build/path.o build/vector.o

all: deps main

$(OBJS): $(BUILD)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@ -I $(INC)

main: $(OBJS)
	$(CC) $(OBJS) -o main -I $(INC)

deps: $(OBJS)
