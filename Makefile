#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa main
# Autor		: Cecília Junqueira V. M. Pereira (ceciliajunq@ufmg.br), baseado no Makefile do prof. Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2023-10-03 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo e executa exemplo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/segTree.o $(OBJ)/node.o
HDRS = $(INC)/segTree.hpp $(INC)/node.hpp
CFLAGS = -g -pg -Wall -std=c++17 -c -I$(INC)

EXE = $(BIN)/tp3.out

all: use mem

mem: $(EXE)

use:
	mkdir -p bin/
	mkdir -p obj/
	
$(BIN)/tp3.out: $(OBJS)
	$(CC) -g -o $(BIN)/tp3.out $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp 

$(OBJ)/segTree.o: $(HDRS) $(SRC)/segTree.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/segTree.o $(SRC)/segTree.cpp 

$(OBJ)/node.o: $(HDRS) $(SRC)/node.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/node.o $(SRC)/node.cpp 

clean:
	rm -f $(EXE) $(OBJS) gmon.out