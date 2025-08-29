# Makefile for NASM Assembly (64-bit)

ASM = nasm
LD = ld

ASMFLAGS = -f elf64
LDFLAGS =

SRC = program.asm
OBJ = program.o
BIN = program

all: $(BIN)

$(OBJ): $(SRC)
	$(ASM) $(ASMFLAGS) $(SRC) -o $(OBJ)

$(BIN): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(BIN)

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)
