CC=gcc

C_SOURCES = $(wildcard *.c)
C_HEADERS = $(wildcard *.h)
OBJ = $(patsubst %.c,%.o,$(C_SOURCES))

gfxcrypt.exe: ${OBJ}
	$(CC) $^ -o $@ -lm

%.o: %.c $(C_HEADERS)
	$(CC) -c $< -o $@
