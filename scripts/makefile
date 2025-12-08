CC = gcc
CFLAGS = -Wall -Wextra -I./shared

# -------------------------------
# Definição das fontes e objetos
# -------------------------------

# Collections
COLLECTIONS_SRC = $(wildcard src/collections/*.c)
COLLECTIONS_OBJ = $(patsubst src/%.c,bin/%.o,$(COLLECTIONS_SRC))

# Model
MODEL_SRC = $(wildcard src/model/*.c)
MODEL_OBJ = $(patsubst src/%.c,bin/%.o,$(MODEL_SRC))

# Repo
REPO_SRC = $(wildcard src/repo/*.c)
REPO_OBJ = $(patsubst src/%.c,bin/%.o,$(REPO_SRC))

# View
VIEW_SRC = ./src/views/wrapper.c
VIEW_OBJ = $(patsubst src/%.c,bin/%.o,$(VIEW_SRC))

# -------------------------------
# Receita principal
# -------------------------------
all: main

# -------------------------------
# Executável principal
# -------------------------------
SRC = src/main.c
OBJ = $(patsubst src/%.c,bin/%.o,$(SRC)) $(COLLECTIONS_OBJ) $(MODEL_OBJ) $(REPO_OBJ) $(VIEW_OBJ)

main: $(OBJ)
	$(CC) $(OBJ) -o main

# -------------------------------
# Regras específicas por grupo
# -------------------------------
collections: $(COLLECTIONS_OBJ)
	@echo "Collections compiladas"

model: $(MODEL_OBJ)
	@echo "Model compilado"

repo: $(REPO_OBJ)
	@echo "Repo compilado"

view: $(VIEW_OBJ)
	@echo "Views compiladas"

# -------------------------------
# Regra genérica para compilar .c em .o
# -------------------------------
bin/%.o: src/%.c
ifeq ($(OS),Windows_NT)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
	$(CC) $(CFLAGS) -c $< -o $@

# -------------------------------
# Limpeza
# -------------------------------
clean:
	rm -rf bin main
