SRC = ./src
BUILD = ./build
INC = ./inc
CFLAGS=-g

OBJS = build/matrix.o

all: deps main

run:
	./main

clean:
	$(RM) -r ./build
	$(RM) main

DIR_GUARD = @mkdir -p $(@D)

$(OBJS): $(BUILD)/%.o: $(SRC)/%.c $(INC)/%.h
	$(DIR_GUARD)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main -I $(INC) -lm

deps: $(OBJS)
