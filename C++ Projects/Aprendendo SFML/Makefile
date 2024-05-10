# Definindo variáveis
CXX = g++
SFML_INCLUDE = -I/usr/include/SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Lista de arquivos fonte
SOURCES = src/main.cpp src/Game.cpp

# Nome do executável
EXECUTABLE = main

# Regras de compilação
all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) -g $(SFML_INCLUDE) $^ -o $@ $(SFML_LIBS)

# Alvo para executar o programa
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Regra para limpar
clean:
	rm -f $(EXECUTABLE)
