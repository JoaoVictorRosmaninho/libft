# TASK 001: Arena Allocator - Robustez e Idempotência

**Status:** ⏳ Pendente  
**Prioridade:** 🔴 Alta  
**Complexidade:** 🟡 Média  
**Estimativa:** 8-12 horas

---

## 📋 Descrição

Implementar um sistema robusto de gerenciamento de ciclo de vida para o Arena Allocator, focando em:

1. **Idempotência** - Funções `_destroy()` seguras para chamadas múltiplas
2. **State Machine** - Controle explícito de estados de recursos
3. **Ownership Model** - Clareza sobre quem é responsável por cada recurso
4. **Contratos Explícitos** - Documentação de expectations e invariantes
5. **Testes Abrangentes** - Edge cases, cleanup automático, vazamentos

---

## 🎯 Objetivos

### Objetivo 1: Implementar State Machine para `t_coliseu`

**Problema Atual:**
```c
// Sem estado, impossível saber se uma arena foi destruída
t_coliseu arena;
ft_arena_destroy(&arena);
ft_arena_destroy(&arena);  // ❌ Double free silencioso
```

**Solução:**
```c
typedef enum {
    ARENA_UNINITIALIZED,  // Nunca foi criada
    ARENA_ACTIVE,         // Pronta para usar
    ARENA_DESTROYED       // Foi destruída
} t_arena_state;

typedef struct s_coliseu {
    t_arena_state state;  // ← NEW
    t_arena *door;
    t_arena *region;
    size_t size;
    uint16_t total_arenas;
    enum arena_type type;
} t_coliseu;
```

**Benefícios:**
- ✅ Detectar estados inválidos em tempo de execução
- ✅ Facilitar debugging (saber em qual estado está)
- ✅ Permitir validações no início de funções
- ✅ Documentar transições de estado

---

### Objetivo 2: Tornar `ft_arena_destroy()` Completamente Idempotente

**Checklist de Idempotência:**
- [ ] Ser seguro chamar 2x, 10x, 100x com mesmo ponteiro
- [ ] Não modificar estado global
- [ ] Não liberar já liberado
- [ ] Manter invariantes da estrutura

**Implementação:**

```c
void ft_arena_destroy(t_coliseu *coliseu)
{
    t_arena *arena;
    t_arena *_arena;

    // ✅ Proteção 1: NULL check
    if (!coliseu)
        return;
    
    // ✅ Proteção 2: Verificar estado
    if (coliseu->state == ARENA_DESTROYED)
        return;
    
    // Liberar chain de arenas
    arena = coliseu->door;
    while (arena)
    {
        _arena = arena;
        arena = arena->next;
        free(_arena);
    }
    
    // ✅ Proteção 3: Zerar todos os ponteiros
    coliseu->door = NULL;
    coliseu->region = NULL;
    coliseu->total_arenas = 0;
    
    // ✅ Proteção 4: Marcar estado como destruído
    coliseu->state = ARENA_DESTROYED;
}
```

---

### Objetivo 3: Implementar Validação de Estado

**Criar função auxiliar para validar invariantes:**

```c
/**
 * ft_arena_validate - Valida invariantes de uma coliseu
 * @coliseu: Estrutura a validar
 * 
 * Retorna:
 *   0 se válida
 *   <0 com código de erro se inválida
 * 
 * Invariantes verificadas:
 *   - Se UNINITIALIZED: door e region devem ser NULL
 *   - Se ACTIVE: door e region devem ser não-NULL
 *   - Se DESTROYED: door e region devem ser NULL
 *   - begin <= end sempre
 */
int ft_arena_validate(const t_coliseu *coliseu);
```

**Exemplo de uso:**

```c
int ft_arena_alloc(size_t chunk, t_coliseu *coliseu)
{
    if (ft_arena_validate(coliseu) < 0)
        return (NULL);  // Estado inválido!
    
    // ... resto da lógica ...
}
```

---

### Objetivo 4: Eliminar Side Effects Ocultos

**Problema Atual:**

```c
// ❌ RUIM: ft_printf destroi silenciosamente TODAS as arenas
int ft_printf(const char *format, ...)
{
    va_list arg_list;
    size_t len = 0;

    va_start(arg_list, format);
    len = ft_printf_lexer(format, arg_list);
    va_end(arg_list);

    ft_coliseu_manager(GIVE_BACK);  // ← SIDE EFFECT OCULTO!
    
    return (len);
}
```

**Solução:**

```c
// ✅ BOM: Deixar o chamador controlar cleanup
int ft_printf(const char *format, ...)
{
    va_list arg_list;
    size_t len = 0;

    va_start(arg_list, format);
    len = ft_printf_lexer(format, arg_list);
    va_end(arg_list);
    
    // SEM ft_coliseu_manager(GIVE_BACK)!
    // Deixar caller decidir quando fazer cleanup
    
    return (len);
}

// E adicionar uma função EXPLÍCITA:
void ft_arena_cleanup(void)
{
    ft_coliseu_manager(GIVE_BACK);
}
```

**Benefícios:**
- Explicitamento: quem lê o código vê claramente quando cleanup acontece
- Previsibilidade: sem side effects surpresa
- Testabilidade: fácil mockar ou contolar cleanup
- Performance: caller pode fazer batch cleanup

---

### Objetivo 5: Ownership Model Documentado

**Adicionar comentários nos headers explicando ownership:**

```c
/**
 * @file arena.h
 * 
 * OWNERSHIP MODEL:
 * 
 * 1. GLOBAL SINGLETONS (ft_coliseu_manager)
 *    - Propriedade: libft (singleton global)
 *    - Ciclo de vida: main() até exit()
 *    - Thread-safety: NÃO (single-threaded only)
 *    - Inicialização: Lazy (primeira chamada ft_arena_alloc)
 *    - Cleanup: Implícito (exit) ou explícito (ft_arena_cleanup)
 * 
 * 2. DYNAMIC ARENAS (ft_coliseu_create_on_arena)
 *    - Propriedade: Caller (quem chamou ft_coliseu_create_on_arena)
 *    - Ciclo de vida: Controlado pelo caller
 *    - Thread-safety: NÃO
 *    - Inicialização: Explícita (ft_coliseu_create)
 *    - Cleanup: Responsabilidade do caller (ft_arena_destroy)
 * 
 * 3. STACK ARENAS (aplicação específica)
 *    - Propriedade: Stack frame
 *    - Ciclo de vida: Automático (RAII com __attribute__((cleanup)))
 *    - Thread-safety: Depende de sincronização externa
 */
```

---

## 🧪 Casos de Teste

### Test Suite 1: Idempotência

```c
/**
 * test_arena_destroy_idempotent
 * 
 * Verifica que ft_arena_destroy pode ser chamada múltiplas vezes
 * com segurança, sem corrupção de memória ou double free.
 */
void test_arena_destroy_idempotent(void)
{
    t_coliseu arena = {0};
    
    // Setup
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    
    // Allocate something
    void *ptr1 = ft_arena_alloc(64, &arena);
    void *ptr2 = ft_arena_alloc(128, &arena);
    assert(ptr1 != NULL && ptr2 != NULL);
    
    // Primeira destruição
    ft_arena_destroy(&arena);
    assert(arena.door == NULL);
    assert(arena.region == NULL);
    assert(arena.state == ARENA_DESTROYED);
    
    // Segunda destruição - DEVE SER SEGURA
    ft_arena_destroy(&arena);  // Não deve crashear
    assert(arena.door == NULL);
    assert(arena.region == NULL);
    
    // Terceira destruição - DEVE SER SEGURA
    ft_arena_destroy(&arena);  // Não deve crashear
    assert(arena.door == NULL);
    
    // Até com NULL - DEVE SER SEGURA
    ft_arena_destroy(NULL);     // Não deve crashear
}
```

### Test Suite 2: State Machine

```c
/**
 * test_arena_state_transitions
 * 
 * Verifica que as transições de estado são corretas
 */
void test_arena_state_transitions(void)
{
    t_coliseu arena = {0};
    
    // Estado inicial
    assert(arena.state == ARENA_UNINITIALIZED);
    
    // Após criar
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    assert(arena.state == ARENA_ACTIVE);
    
    // Após destruir
    ft_arena_destroy(&arena);
    assert(arena.state == ARENA_DESTROYED);
    
    // Não deve poder alocar em estado destruído
    void *ptr = ft_arena_alloc(64, &arena);
    assert(ptr == NULL);  // Deve falhar
}
```

### Test Suite 3: Validação de Invariantes

```c
/**
 * test_arena_invariants
 * 
 * Verifica que invariantes de memória são mantidas
 */
void test_arena_invariants(void)
{
    t_coliseu arena = {0};
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    
    // Allocate 1KB
    void *ptr = ft_arena_alloc(1024, &arena);
    
    // Invariante 1: begin nunca ultrapassa end
    assert(arena.region->begin <= arena.region->end);
    
    // Invariante 2: disponível > 0 após criação
    assert(arena.region->avaliable > 0);
    
    // Invariante 3: disponível < original
    size_t before = ARENA_32KB;
    size_t after = arena.region->avaliable;
    assert(after < before);
    
    ft_arena_destroy(&arena);
}
```

### Test Suite 4: Memory Leak Detection

```c
/**
 * test_arena_no_memory_leaks
 * 
 * Executar com: valgrind --leak-check=full ./test_runner
 * 
 * Verifica que não há vazamento de memória em ciclos completos
 */
void test_arena_no_memory_leaks(void)
{
    for (int i = 0; i < 1000; i++)
    {
        t_coliseu arena = {0};
        arena.size = ARENA_32KB;
        ft_coliseu_create(&arena);
        
        // Allocate and destroy multiple times
        for (int j = 0; j < 100; j++)
            ft_arena_alloc(64, &arena);
        
        ft_arena_destroy(&arena);
    }
    // Valgrind deve reportar 0 leaks
}
```

### Test Suite 5: Global Arena Manager (Fixture)

```c
/**
 * test_global_arena_manager
 * 
 * Testa o gerenciador global com cleanup explícito
 */
void test_global_arena_manager(void)
{
    // ANTES: Usar o manager silenciosamente
    t_coliseu *arena = ft_coliseu_manager(TAKE);
    void *ptr = ft_arena_alloc(512, arena);
    
    // Agora com cleanup EXPLÍCITO
    ft_arena_cleanup();  // ← Claro e documentado
    
    // Tentar alocar novamente deve funcionar (reinicia)
    arena = ft_coliseu_manager(TAKE);
    void *ptr2 = ft_arena_alloc(512, arena);
    assert(ptr2 != NULL);
    
    ft_arena_cleanup();
}
```

---

## 📚 Referências e Padrões de Design

### 1. **State Machine Pattern**

**Referências Literárias:**
- "Design Patterns: Elements of Reusable Object-Oriented Software" (Gang of Four, 1994)
  - Cap. 5: Behavioral Patterns → State Pattern
- "Pattern-Oriented Software Architecture" (POSA), vol. 1
  - Cap. 3: State Machine Pattern

**Aplicação em C:**
```c
// Simples enum basado
typedef enum { IDLE, RUNNING, STOPPED } state_t;

// Ou máquina de estado mais sofisticada
typedef struct {
    state_t current;
    void (*on_enter)(void);
    void (*on_exit)(void);
    int (*on_event)(event_t);
} state_machine_t;
```

**Benefício:**
- Explicitamente clara representação de estado
- Facilita debugging
- Evita estados inválidos

---

### 2. **Idempotence / Idempotent Operations**

**Conceito Matemático:**
```
f(f(x)) = f(x)  // Chamar múltiplas vezes é seguro
```

**Referências:**
- "The C Programming Language" (K&R, 2ª ed.) - Cap. 8: The Unix System Interface
- RFC 7231 (HTTP Semantics) - Seção 4.2.1: Safe Methods (GET, HEAD)
  - Define idempotência como safety property

**Em C:**
- `free()` não é idempotente
- `close()` é idempotente (fechar arquivo já fechado = noop)
- `pthread_mutex_destroy()` não é idempotente

**Padrão em libft:**
```c
// ✅ Idempotente
void cleanup(Resource *r) {
    if (!r || r->cleaned)
        return;
    free(r->data);
    r->cleaned = 1;  // ← Marca como processado
}

// ❌ Não idempotente
void cleanup(Resource *r) {
    free(r->data);  // Segunda vez = undefined behavior
}
```

---

### 3. **RAII - Resource Acquisition Is Initialization**

**Origem:**
- Bjarne Stroustrup em C++ (1998)
- Implementável em C com `__attribute__((cleanup))`

**Conceito:**
```
Resource lifetime = Scope lifetime
```

**Referências:**
- "The C++ Programming Language" (Stroustrup, 4ª ed.)
  - Cap. 13: Exception Handling → RAII
- "Exceptional C++" (Herb Sutter, 2000)

**Em C:**
```c
static inline void cleanup_arena(t_coliseu **a) {
    ft_arena_destroy(*a);
}

#define ARENA_AUTO __attribute__((cleanup(cleanup_arena)))

// Uso
void func(void) {
    ARENA_AUTO t_coliseu my_arena = {0};
    // ... use my_arena ...
    // ← Automaticamente destruída aqui
}
```

---

### 4. **RAII Patterns - Ownership Models**

**Referências:**
- "Rust Book" - Cap. 4: Ownership
  - https://doc.rust-lang.org/book/ch04-00-understanding-ownership.html
  - Ownership, Borrowing, Lifetime
- "The C Programming Language" - Cap. 6: Structures

**Padrões em libft:**

```c
// 1. OWNED - Responsável por destruir
typedef struct {
    char *data;  // Eu possuo isso
} Owned;

// 2. BORROWED - Temporário, não destruir
typedef struct {
    const char *data;  // Alguém mais possui
} Borrowed;

// 3. SHARED - Contagem de referência
typedef struct {
    char *data;
    int *ref_count;
} Shared;
```

---

### 5. **Invariants and Contracts (Design by Contract)**

**Origem:**
- Bertrand Meyer, Eiffel (1986)

**Referências:**
- "Object-Oriented Software Construction" (Meyer, 1997)
  - Cap. 11: Contracts, Assertions and Exceptions
- "Code Complete" (Steve McConnell, 2004)
  - Cap. 8: Defensive Programming

**Em libft:**

```c
/**
 * PRECONDITIONS (deve ser verdadeiro antes)
 * - coliseu != NULL
 * - coliseu->state == ARENA_ACTIVE
 * 
 * POSTCONDITIONS (deve ser verdadeiro depois)
 * - coliseu->region->begin <= coliseu->region->end
 * - coliseu->region->avaliable >= 0
 * 
 * INVARIANTS (sempre verdadeiro)
 * - door é head da linked list
 * - region aponta para um nó válido
 * - total_arenas >= 1 se ACTIVE
 */
void *ft_arena_alloc(size_t chunk, t_coliseu *coliseu)
{
    // Verificar precondições
    if (!coliseu || coliseu->state != ARENA_ACTIVE)
        return (NULL);
    
    // ... resto da lógica ...
    
    // Verificar postcondições
    assert(coliseu->region->begin <= coliseu->region->end);
    assert(coliseu->region->avaliable >= 0);
}
```

---

### 6. **Defensive Programming**

**Referências:**
- "Code Complete" (Steve McConnell, 2004)
  - Cap. 8: Defensive Programming (Seção 8.1-8.4)
- "The Pragmatic Programmer" (Hunt & Thomas, 2019)
  - Cap. 4: Pragmatic Paranoia

**Aplicação em libft:**

```c
// Defensive principle: Never trust input
void ft_arena_destroy(t_coliseu *coliseu)
{
    // ✅ Defensive 1: NULL check
    if (!coliseu)
        return;
    
    // ✅ Defensive 2: State check
    if (coliseu->state == ARENA_DESTROYED)
        return;
    
    // ✅ Defensive 3: Invariant check
    if (coliseu->door && coliseu->region)
        // ... liberar ...
    
    // ✅ Defensive 4: Clear state
    coliseu->door = NULL;
    coliseu->region = NULL;
}
```

---

## 📊 Impacto e Benefícios

| Métrica | Antes | Depois |
|---------|-------|--------|
| **Memory Safety** | 🔴 Duplo free possível | 🟢 Protegido |
| **Debuggability** | 🟡 Sem estado visível | 🟢 Estado claro |
| **Testability** | 🟡 Difícil testar cleanup | 🟢 Fácil mockar |
| **Performance** | 🟢 N/A | 🟢 N/A (sem overhead) |
| **Maintainability** | 🟡 Contrato implícito | 🟢 Contrato explícito |
| **Documentation** | 🟡 Sem exemplos | 🟢 Bem documentado |

---

## 📅 Timeline de Implementação

1. **Fase 1 (2h):** Adicionar enum `t_arena_state` e atualizar estrutura
2. **Fase 2 (2h):** Implementar `ft_arena_validate()` e `ft_arena_destroy()` idempotente
3. **Fase 3 (2h):** Remover side effects (`ft_arena_cleanup()` explícito)
4. **Fase 4 (2h):** Escrever testes abrangentes (5+ suites)
5. **Fase 5 (2h):** Documentação e comentários no código
6. **Fase 6 (1h):** Valgrind check e análise de performance
7. **Fase 7 (1h):** Code review e ajustes finais

---

## ✅ Checklist de Conclusão

- [ ] State machine implementado
- [ ] `ft_arena_destroy()` é idempotente
- [ ] `ft_arena_validate()` implementada
- [ ] Side effects removidos (ou explícitos)
- [ ] Ownership model documentado
- [ ] 5+ test suites passando
- [ ] Valgrind 100% limpo
- [ ] Headers com comentários/contratos
- [ ] README.md atualizado
- [ ] Examples/arena_usage.c criado

---

## 📖 Referências Externas

### Livros
1. "The C Programming Language" - Kernighan & Ritchie (1988)
2. "Design Patterns" - Gang of Four (1994)
3. "Code Complete" - Steve McConnell (2004)
4. "The Pragmatic Programmer" - Hunt & Thomas (2019)

### Documentos Online
1. https://en.wikipedia.org/wiki/Idempotence
2. https://doc.rust-lang.org/book/ch04-00-understanding-ownership.html
3. RFC 7231: HTTP Semantics (Idempotent Methods)
4. https://en.cppreference.com/w/cpp/memory/unique_ptr

### Padrões de Design Relacionados
- State Pattern (Gang of Four)
- Singleton Pattern (Gang of Four)
- Factory Pattern (Gang of Four)
- Resource Acquisition Is Initialization (RAII)
- Double-Checked Locking (para thread safety futura)

---

**Última Atualização:** 6 de dezembro de 2025  
**Autor:** Code Review  
**Status:** Aguardando Implementação
