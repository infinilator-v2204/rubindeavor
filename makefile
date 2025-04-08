CC=gcc

C_SOURCES = $(wildcard *.c)
C_HEADERS = $(wildcard *.h)
OBJ = $(patsubst %.c,_obj/%.o,$(C_SOURCES))

rubindeavor.exe: ${OBJ} _obj/resource.o
	$(CC) $^ -o $@ -mconsole -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -s

_obj/resource.o: resource.rc
	windres $< -o $@

_obj/%.o: %.c $(C_HEADERS)
	$(CC) -c $< -o $@ -Wno-pointer-sign
