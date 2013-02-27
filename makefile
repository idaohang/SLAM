SRC = ./src
BUILD = ./build
INC = ./inc

OBJS = build/llist.o build/path.o build/vector.o

all: deps main

run:
	./main

clean:
	$(RM) -r ./build
	$(RM) main

DIR_GUARD = @mkdir -p $(@D)

$(OBJS): $(BUILD)/%.o: $(SRC)/%.c
	$(DIR_GUARD)
	$(CC) -g -c $< -o $@ -I $(INC)

main: $(OBJS)
	$(CC) $(OBJS) -o main -I $(INC)

deps: $(OBJS)
