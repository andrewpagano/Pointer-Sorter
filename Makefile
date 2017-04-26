CC = gcc
FILES = mymalloc.c memgrind.c mymalloc.h
OUT_EXE = out_executable

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o core

rebuild: clean build