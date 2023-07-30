CC = g++
CCFLAGS =
LIB =
EXEC = server

SUPP = rm -rf

#Tous les fichiers .c
SRC = $(wildcard *.c)
SRC2 = $(wildcard lib/*.c)
SRC3 = $(wildcard *.cpp)
#Générer les noms des fichiers .o à partir de la liste des fichiers .c
OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.cpp=.o)

all: $(EXEC)

$(EXEC) : $(OBJ) $(OBJ2) $(OBJ3)
	$(CC) -o $@ $^ $(CCFLAGS) $(LIB)

%.o : %.c
	$(CC) -o $@ -c $< $(CCFLAGS) $(LIB)

clean:
	@echo "Suppression des fichiers $(OBJ)"
	$(SUPP) $(OBJ) $(OBJ2) $(OBJ3)

mrproper: clean
	$(SUPP) $(EXEC)

rebuild: mrproper all
