SRC = ./src
BUILD = ./build
INC = ./inc

CMD = $(CC) -m64 -W -Wall

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
	$(CMD) -g -c $< -o $@ -I $(INC)

main: $(OBJS)
	$(CMD) $(OBJS) -o main -I $(INC) -lm

deps: $(OBJS)
