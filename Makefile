# Executable
EXEC=katrologger
BIN=/usr/bin/

# Compiler
CC=gcc

# .c sources
C_SRC=$(wildcard ./src/*.c)

# .h headers
H_SRC=$(wildcard ./src/*.h)

# Object files
OBJ=$(subst .c,.o,$(subst src,objs,$(C_SRC)))

# Flags
CC_FLAGS=-w         \
         -lX11      \
         -lquickmail

all: objFolder $(EXEC)

$(EXEC): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@ $(CC_FLAGS)
	@ echo 'Finished building binary: $@'
	@ echo ' '

./objs/%.o: ./src/%.c ./src/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) -c $< -o $@ -w
	@ echo ' '

./objs/main.o: ./src/main.c $(H_SRC)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) -c $< -o $@
	@ echo ' '

objFolder:
	@ mkdir -p objs

clean:
	@ rm -rf ./objs/*.o $(EXEC)
	@ rmdir objs

.PHONY: all clean

make install:
	@ mv $(EXEC) $(BIN)
	@ echo "$(EXEC) --> $(BIN)"

uninstall:
	@ rm -f $(BIN)$(EXEC)
