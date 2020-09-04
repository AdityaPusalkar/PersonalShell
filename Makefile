all: build

build:
	gcc personalshell.c cat.c cd.c cp.c chmod.c grep.c ls.c mkdir.c mv.c rm.c -o shell -Wall -Werror

clean:
	rm shell
