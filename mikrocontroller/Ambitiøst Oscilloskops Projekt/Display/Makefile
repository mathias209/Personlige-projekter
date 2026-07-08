LDFLAGS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -Iinclude
CCFLAGS=-Og -std=c23

targets = $(patsubst %.c,%.o,$(wildcard src/*.c))
libtargets = $(patsubst %.c,%.so,$(wildcard lib/*.c))
depends = $(patsubst %.c,%.d,$(wildcard src/*.c))

all: build

build: main

run: main
	./main

debug: main
	gdb main

clean:
	rm -f main compile_commands.json $(targets) $(libtargets) $(depends)

bear:
	bear -- make

main: $(targets) $(libtargets)
	gcc -o main $(LDFLAGS) $(CCFLAGS) $(targets) $(libtargets)

-include $(depends)

$(targets): %.o: %.c Makefile
	gcc $(LDFLAGS) $(CCFLAGS) -MMD -MP -c $< -o $@

$(libtargets): %.so: %.c
	gcc $(LDFLAGS) $(CCFLAGS) -c $< -o $@
