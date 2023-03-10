##########################################
#           Editable options             #
##########################################

# Compiler options
CC=cc
CFLAGS=-Wall -Wextra -Werror -g3

LDFLAGS=
BINARY_NAME_1=server
BINARY_NAME_2=client

# Folders
SRC=src
INC=-I ./inc
OBJ=obj

# Files
SOURCE_NAME= utils.c \
			 parse.c \
			 minitalk.c \
			 server.c \
			 client.c

##########################################
#    Don't touch anything below this     #
##########################################
SOURCE_FILES     = $(SOURCE_NAME:%.c=$(SRC)/%.c)
OBJECT_FILES_1   = $(OBJ)/utils.o $(OBJ)/parse.o $(OBJ)/minitalk.o $(OBJ)/server.o
OBJECT_FILES_2   = $(OBJ)/utils.o $(OBJ)/parse.o $(OBJ)/minitalk.o $(OBJ)/client.o

build: $(BINARY_NAME_1) $(BINARY_NAME_2)

clean:
	@echo Removing $(OBJ)...
	@rm -r -f $(OBJ)

fclean: clean
	@echo Removing $(BINARY_NAME_1)...
	@rm -r -f $(BINARY_NAME_1)
	@echo Removing $(BINARY_NAME_2)...
	@rm -r -f $(BINARY_NAME_2)

re: fclean build

.PHONY: re clean fclean build

$(BINARY_NAME_1): $(OBJECT_FILES_1)
	@echo Linking $+...
	@$(CC) -o $(BINARY_NAME_1) $+
	@echo $(BINARY_NAME_1) "created succesfully!"

$(BINARY_NAME_2): $(OBJECT_FILES_2)
	@echo Linking $+...
	@$(CC) -o $(BINARY_NAME_2) $+
	@echo $(BINARY_NAME_2) "created succesfully!"

$(OBJ)/%.o: $(SRC)/%.c
	@echo Compiling $<...
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
