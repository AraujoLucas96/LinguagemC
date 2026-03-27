# Nome do executável
EXECUTAVEL = program

# Arquivos fonte
FONTES = program.c Headers/db.c

# Compilador
CC = gcc

# Flags (opcional, mas recomendado)
CFLAGS = -Wall -Wextra

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(FONTES)
	$(CC) $(FONTES) -o $(EXECUTAVEL) $(CFLAGS)

clean:
	rm -f $(EXECUTAVEL)