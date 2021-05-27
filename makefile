CC = gcc 															# Compiler
CFLAGS = -Wall -O 													# Compiler options
LDFLAGS = 															# Compiler links edition

MODULES = . parser_test	nanoml_loader								# All the modules to compile

EXEC = executable 												    # Executables name
SRC = $(foreach sdir,$(MODULES), $(wildcard $(sdir)/*.c))			# Fetch all the *.c files
OBJ = $(SRC:.c=.o)													# Create all objects files


all: $(EXEC)														# Executable link

$(EXEC): $(OBJ)														# Executable dependances
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c															# Objects dependances
	$(CC) -o $@ -c $^ $(CFLAGS)

# Clean project

clean:
	rm -f $(OBJ)
	rm -f $(EXEC)
	rm -f *.stackdump

run:
	make clean
	make all
	./$(EXEC)