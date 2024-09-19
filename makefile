CC=gcc

C_SOURCES = $(wildcard *.c)
C_HEADERS = $(wildcard *.h)
OBJ = $(patsubst %.c,_obj/%.o,$(C_SOURCES))

rubixplore: ${OBJ}
	$(CC) $^ -o $@ -lm -lSDL2 -lSDL2_image -lSDL2_mixer -lzip

_obj/%.o: %.c $(C_HEADERS)
	$(CC) -c $< -o $@
