SRC = ./src
BUILD = ./build
INC = ./inc

CMD = $(CC) -m64

OBJS = build/slam.o build/path.o build/llist.o build/vector.o

all: deps main

run:
	./main

clean:
	$(RM) -r ./build
	$(RM) main

DIR_GUARD = @mkdir -p $(@D)

$(OBJS): $(BUILD)/%.o: $(SRC)/%.c $(INC)/%.h
	$(DIR_GUARD)
	$(CMD) -g -c $< -o $@ -I $(INC)

main: $(OBJS)
	$(CMD) $(OBJS) -o main -I $(INC)

deps: $(OBJS)
