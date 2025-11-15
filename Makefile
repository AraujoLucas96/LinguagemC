# Define o nome do seu executável
EXECUTAVEL = program

# Define o nome do seu arquivo fonte
FONTE = program.c

# Define o caminho de inclusão (Header) e de biblioteca (Linker)
# Como sabemos o caminho exato, podemos usá-lo diretamente
INCLUDE_PATH = -I/usr/include/postgresql
LIB_FLAG = -lpq

# O comando de compilação
all: $(EXECUTAVEL)

$(EXECUTAVEL): $(FONTE)
	gcc $(FONTE) -o $(EXECUTAVEL) $(INCLUDE_PATH) $(LIB_FLAG)

# Comando para limpar os arquivos gerados (opcional, mas útil)
clean:
	rm -f $(EXECUTAVEL)