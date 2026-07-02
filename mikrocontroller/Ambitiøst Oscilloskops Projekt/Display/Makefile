LDFLAGS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -Iinclude
CCFLAGS=-Og

targets = $(patsubst %.c,%.o,$(wildcard src/*.c))
libtargets = $(patsubst %.c,%.so,$(wildcard lib/*.c))

all: build

build: main

run: main
	./main

debug: main
	gdb main

clean:
	rm -f main compile_commands.json $(targets) $(libtargets)

bear:
	bear -- make


main: $(targets) $(libtargets)
	gcc -o main $(LDFLAGS) $(CCFLAGS) $(targets) $(libtargets)

$(targets): %.o: %.c
	gcc $(LDFLAGS) $(CCFLAGS) -c $< -o $@

$(libtargets): %.so: %.c
	gcc $(LDFLAGS) $(CCFLAGS) -c $< -o $@
