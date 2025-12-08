Alunas: Julia almeida e Elisa Andrade

# 📘 Sistema de Gerenciamento de Times e Partidas

Este projeto implementa um sistema completo para gerenciamento de **times**, **partidas**, **estatísticas**, **classificação** e **consultas**, utilizando **estruturas de dados dinâmicas**, **listas encadeadas**, **modularização** e um modelo de “banco de dados em memória”.

O objetivo é demonstrar domínio de C estruturado, abstração em camadas, organização modular e manipulação eficiente de dados.

---

## 📑 Sumário

1. [Arquitetura do Projeto](#arquitetura-do-projeto)
2. [Funcionalidades Principais](#funcionalidades-principais)
3. [Estruturas de Dados](#estruturas-de-dados)
4. [Views Implementadas](#views-implementadas)
5. [Menu Principal](#menu-principal)
6. [Compilação e Execução](#compilação-e-execução)
7. [Dependências](#dependências)
8. [Observações Importantes](#observações-importantes)

---

# 🧱 Arquitetura do Projeto

A organização segue uma estrutura modular limpa:

```
/src
├── model (Modelos: Time, Partida)
├── repo (Banco em memória: TimeDB, PartidaDB)
├── view (Views de interação com o usuário)
├── utils (Funções auxiliares: leitura robusta)
└── main.c (Ponto de entrada)
```


### ✔ `model/`
Contém as definições das entidades:
- `Time`
- `Partida`
- `TimeDB`
- `PartidaDB`

### ✔ `repo/`
Implementa operações sobre o banco em memória:
- Inserir partidas
- Remover partidas
- Buscar por prefixo
- Buscar por mandante/visitante
- Ordenar dados

### ✔ `view/`
Contém todas as interfaces de interação com o usuário:
- Consulta de times
- Consulta de partidas
- Inserção, atualização e remoção de partidas
- Classificação com paginação
- Menu principal

### ✔ `utils/`
Funções robustas para entrada do usuário:
- `readInt()`
- `readString()`
- `readChar()`

---

# ⚙️ Funcionalidades Principais

O sistema oferece:

### ✔ Consulta de Times
- Busca por prefixo do nome
- Cálculo automático de:
  - Vitórias, Empates, Derrotas
  - Gols marcados e sofridos
  - Saldo
  - Pontos

### ✔ Consulta de Partidas
Busca por:
- Mandante  
- Visitante  
- Mandante ou visitante  

### ✔ Atualizar Partida
- Usuário informa o ID
- Pode substituir somente gols
- Permite manter valores anteriores usando `-`
- Confirmação com `S/N`

### ✔ Remover Partida
- Busca por critério
- Exibe resultados
- Usuário seleciona o ID
- Confirma remoção
- Libera memória corretamente (`freePartida()` + `llRemoveFirstFound()`)

### ✔ Inserir Partida
- Usuário informa ID dos times e gols
- Validação por enum retornado:
  - Times iguais
  - Times inexistentes
  - Falta de memória
  - Ponteiro nulo
- Mensagens claras para cada erro

### ✔ Tabela de Classificação (Paginada)
- Ordenada por pontos
- 5 times por página
- Navegação por número
- Sair com `Q`

---

# 🗂 Estruturas de Dados

### `Time`
```c
typedef struct Time {
    int id;
    char name[TIME_MAX_NAME_SIZE];
} Time;

typedef struct Partida {
    int id;
    Time* t1;
    Time* t2;
    int golsT1;
    int golsT2;
} Partida;

typedef struct TimeDB {
    LinkedList* times;
} TimeDB;

typedef struct PartidaDB {
    LinkedList* partidas;
} PartidaDB;
```

# 👁️ Views Implementadas
## ✔ View de Consulta de Times

Usuário digita prefixo

Busca com searchByPrefix()

Imprime tabela com estatísticas calculadas dinamicamente

## ✔ View de Consulta de Partidas

Usuário escolhe entre:

Mandante

Visitante

Ambos

Digita prefixo

Resultado exibido em tabela

## ✔ View de Atualização de Partidas

Edita gols mantendo valores antigos com -

Confirmação antes de salvar

## ✔ View de Remoção de Partidas

Busca

Exibição

Seleção de ID

Confirmação

Remoção com desalocação segura

## ✔ View de Inserção de Partidas

Usuário informa IDs e gols

Tratamento completo de erros via enum:
```
NULL_POINTER_EXCEPTION
MEMORY_NOT_ENOUGH_EXCEPTION
TIME_1_EQUALS_TIME_2
TIME_1_DOES_NOT_EXISTS
TIME_2_DOES_NOT_EXISTS
SUCCESS
```

## ✔ View de Classificação Paginada

Ordenação por pontos

Paginada (máx. 5 por página)

Navegação por números

Sair com Q

# 🧭 Menu Principal

A view do menu apresenta:

```
=====================================
           MENU PRINCIPAL
=====================================
1 - Consultar Time
2 - Consultar Partidas
3 - Atualizar Partida
4 - Remover Partida
5 - Inserir Partida
6 - Imprimir Tabela de Classificacao
Q - Sair
=====================================
```

A função retorna apenas a opção escolhida (char).

## 🛠 Compilação e Execução
Compilar:
make all

Executar:
`./main` no Windows.
`. ./main` no Linux.


📦 Dependências
Não usa nenhuma biblioteca externa.

⚠️ Observações Importantes

Listas retornadas por funções de busca devem ser liberadas apenas no wrapper, nunca os objetos reais (times/partidas).

Views não alteram o banco diretamente — apenas chamam funções da camada repo.

As buscas por prefixo seguem a regra definida por searchByPrefix().

Estatísticas dos times são recalculadas toda vez que são exibidas, garantindo precisão.

---

