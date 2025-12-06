# Design Patterns em C - Referência Teórica

Este documento fornece uma base teórica sólida sobre padrões de design aplicáveis a libft, com referências literárias e implementações práticas.

---

## 📖 Índice

1. [State Pattern](#state-pattern)
2. [Idempotence Pattern](#idempotence-pattern)
3. [RAII Pattern](#raii-pattern)
4. [Design by Contract](#design-by-contract)
5. [Defensive Programming](#defensive-programming)
6. [Referências Literárias Completas](#referências-literárias-completas)

---

## State Pattern

### Definição Teórica

**Origem:** Gang of Four, "Design Patterns: Elements of Reusable Object-Oriented Software" (1994), pp. 305-313

**Propósito:**
> "Allow an object to alter its behavior when its internal state changes. 
>  The object will appear to change its class."

**Aplicabilidade:**
- Comportamento de um objeto depende de seu estado
- Precisa alternar entre múltiplos estados
- Operações com grandes seções condicionais (if/switch por estado)

### Implementação em C

```c
// ============================================================================
// State definition
// ============================================================================

typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED
} task_state_t;

// ============================================================================
// Context (the object that has state)
// ============================================================================

typedef struct {
    task_state_t state;
    void (*on_enter)(struct s_task *self);
    void (*on_exit)(struct s_task *self);
    void (*process)(struct s_task *self);
} task_t;

// ============================================================================
// State-specific handlers
// ============================================================================

void idle_enter(task_t *self) {
    ft_printf("Task: entering IDLE state\n");
    self->state = STATE_IDLE;
}

void idle_process(task_t *self) {
    // Do nothing
    ft_printf("Task: idle, waiting for input\n");
}

void running_enter(task_t *self) {
    ft_printf("Task: entering RUNNING state\n");
    self->state = STATE_RUNNING;
}

void running_process(task_t *self) {
    ft_printf("Task: executing work...\n");
    // Eventually transition to PAUSED or STOPPED
}

// ============================================================================
// State machine controller
// ============================================================================

int task_transition(task_t *self, task_state_t new_state) {
    // Validate transition
    if (new_state == self->state)
        return 0;  // No change
    
    // Exit current state
    if (self->on_exit)
        self->on_exit(self);
    
    // Update state and enter new state
    self->state = new_state;
    if (self->on_enter)
        self->on_enter(self);
    
    return 1;  // Transition successful
}

// ============================================================================
// Usage example
// ============================================================================

int main(void) {
    task_t my_task = {
        .state = STATE_IDLE,
        .on_enter = idle_enter,
        .on_exit = NULL,
        .process = idle_process
    };
    
    // Transition: IDLE -> RUNNING
    task_transition(&my_task, STATE_RUNNING);
    my_task.on_enter = running_enter;
    my_task.process = running_process;
    
    // Process in current state
    my_task.process(&my_task);
    
    return 0;
}
```

### Aplicação em Arena (TASK_001)

```c
// States
typedef enum {
    ARENA_UNINITIALIZED,  // -> can be created
    ARENA_ACTIVE,         // -> can be destroyed
    ARENA_DESTROYED       // -> can be destroyed again (idempotent)
} t_arena_state;

// Transition rules
struct {
    from,
    to,
    condition,
    action
} transitions[] = {
    { UNINITIALIZED, ACTIVE,    always,    ft_coliseu_create },
    { ACTIVE,        DESTROYED,  always,    ft_arena_destroy },
    { DESTROYED,     DESTROYED,  always,    no_op (safe) }
};
```

### Benefícios em libft

| Aspecto | Benefício |
|---------|----------|
| **Clarity** | Estado explícito, fácil debugar |
| **Safety** | Impossível estar em estado inválido |
| **Extensibility** | Adicionar novos estados é simples |
| **Testing** | Testar cada estado separadamente |

---

## Idempotence Pattern

### Definição Teórica

**Origem:** Teoria Matemática, RFC 7231 (HTTP Semantics)

**Definição Matemática:**
```
Uma função f é idempotente se:
    f(f(x)) = f(x)
    f(f(f(x))) = f(x)
    f^n(x) = f(x) para todo n ≥ 1
```

**Em Programação:**
> "Uma operação idempotente pode ser chamada múltiplas vezes 
>  sem causar efeitos colaterais adicionais após a primeira execução."

### Exemplos do Mundo Real

| Operação | Idempotente? | Motivo |
|----------|-------------|--------|
| `close(fd)` | ✅ Sim | Segunda chamada = noop |
| `free(ptr)` | ❌ Não | Double-free = erro |
| HTTP GET | ✅ Sim | Não modifica estado |
| HTTP POST | ❌ Não | Cada POST cria novo recurso |
| `rm file.txt` | ✅ Sim | Segunda execução = arquivo já foi |
| `mkdir dir` | ❌ Não | Segunda = erro (dir existe) |

### Implementação de Função Idempotente

```c
// ============================================================================
// BAD - Not idempotent
// ============================================================================

int bad_cleanup(Resource *r) {
    if (!r)
        return -1;
    
    free(r->data);
    // r->data ainda aponta para memória liberada!
    
    return 0;
}

// Primeira chamada: OK
bad_cleanup(&resource);

// Segunda chamada: ❌ CRASH - double free
bad_cleanup(&resource);

// ============================================================================
// GOOD - Idempotent
// ============================================================================

int good_cleanup(Resource *r) {
    if (!r || r->cleaned)  // ← Check state
        return 0;
    
    if (r->data) {
        free(r->data);
        r->data = NULL;    // ← Clear pointer
    }
    
    r->cleaned = 1;       // ← Mark as processed
    return 0;
}

// Primeira chamada: OK
good_cleanup(&resource);

// Segunda chamada: ✅ OK - idempotent
good_cleanup(&resource);

// Centésima chamada: ✅ OK - still safe
for (int i = 0; i < 100; i++)
    good_cleanup(&resource);
```

### Padrão Idempotente Robusto

```c
/**
 * Padrão de 4 camadas para garantir idempotência:
 * 1. NULL check
 * 2. State check
 * 3. Perform operation
 * 4. Clear state
 */

void destroy_resource(Resource *r) {
    // Layer 1: NULL check
    if (!r)
        return;
    
    // Layer 2: State check (already processed?)
    if (r->state == STATE_DESTROYED)
        return;
    
    // Layer 3: Do the work
    if (r->data) {
        free(r->data);
    }
    
    // Layer 4: Clear state definitively
    r->data = NULL;
    r->state = STATE_DESTROYED;
    r->size = 0;
    // ← Now safe to call again
}
```

### Idempotência em HTTP (RFC 7231)

O padrão HTTP define idempotência para métodos:

```
GET    /resource   → Idempotent (read-only)
POST   /resource   → Not idempotent (creates new each time)
PUT    /resource   → Idempotent (replace, same result)
DELETE /resource   → Idempotent (delete, already gone = OK)
PATCH  /resource   → Usually not idempotent
```

**Aplicação em libft:**

```c
// Operações de libft e sua idempotência

// ✅ Idempotent
ft_arena_destroy(&arena);    // Seguro chamar 2x
ft_coliseu_free(&arena);      // Seguro chamar 2x
close(fd);                     // Seguro chamar 2x (Unix)

// ❌ NOT idempotent
free(ptr);                     // ❌ Double free = crash
ft_arena_alloc(...);           // ❌ Cada chamada aloca novo
ft_arena_create(...);          // ❌ Cada chamada cria nova arena
```

---

## RAII Pattern

### Definição Teórica

**Origem:** Bjarne Stroustrup em C++, "The C++ Programming Language" (1998)

**Principio:**
> "Resource Acquisition = Constructor Invocation  
>  Resource Release = Destructor Invocation"

```
Aquisição de recurso    → Inicialização (construtor)
Duração de vida         → Escopo (lifetime)
Liberação de recurso    → Finalização (destrutor)
```

### Implementação em C com __attribute__((cleanup))

```c
// ============================================================================
// Traditional C pattern (error-prone)
// ============================================================================

void process_traditional(void) {
    FILE *fp = fopen("file.txt", "r");
    
    if (!fp)
        return;  // ❌ Vaza se fopen falha
    
    if (do_something(fp) < 0) {
        fclose(fp);
        return;  // ✅ Cleanup aqui
    }
    
    if (do_another(fp) < 0) {
        fclose(fp);
        return;  // ✅ Cleanup aqui também
    }
    
    fclose(fp);  // ✅ Cleanup normal
    // ❌ Múltiplos pontos de cleanup = erro fácil
}

// ============================================================================
// RAII pattern with __attribute__((cleanup))
// ============================================================================

// 1. Define cleanup function (called at scope exit)
static inline void file_cleanup(FILE **fp) {
    if (fp && *fp)
        fclose(*fp);
}

// 2. Macro for convenience
#define FILE_AUTO __attribute__((cleanup(file_cleanup)))

// 3. Use in code
void process_raii(void) {
    FILE_AUTO *fp = fopen("file.txt", "r");
    
    if (!fp)
        return;  // ✅ Cleanup happens automatically
    
    if (do_something(fp) < 0)
        return;  // ✅ Cleanup happens automatically
    
    if (do_another(fp) < 0)
        return;  // ✅ Cleanup happens automatically
    
    // ✅ Cleanup happens automatically here
    // Apenas UM ponto de cleanup!
}

// Benefício: 0 leaks, sem duplicação
```

### Aplicação em Arena (TASK_001 Future)

```c
// 1. Cleanup function
static inline void arena_cleanup(t_coliseu **arena) {
    if (arena && *arena)
        ft_arena_destroy(*arena);
}

// 2. Convenience macro
#define ARENA_AUTO __attribute__((cleanup(arena_cleanup)))

// 3. Usage
void frame_processing(void) {
    ARENA_AUTO t_coliseu frame_arena = {0};
    
    frame_arena.size = ARENA_32KB;
    ft_coliseu_create(&frame_arena);
    
    char *temp1 = ft_arena_alloc(256, &frame_arena);
    char *temp2 = ft_arena_alloc(512, &frame_arena);
    
    // Automaticamente destruída ao sair do escopo
    // Nenhuma chamada explícita necessária
}
```

### Benefícios RAII

| Aspecto | Tradicional | RAII |
|---------|------------|------|
| **Pontos de Cleanup** | Múltiplos | 1 (automático) |
| **Vazamento de Memória** | Possível | Impossível |
| **Legibilidade** | Complexa | Clara |
| **Manutenibilidade** | Difícil | Fácil |

---

## Design by Contract

### Definição Teórica

**Origem:** Bertrand Meyer, Eiffel (1986), "Object-Oriented Software Construction" (1997)

**Conceito:**
```
        ┌─────────────────────────────────────┐
        │   Function/Operation Contract        │
        ├─────────────────────────────────────┤
        │ PRECONDITIONS (input valid?)        │
        │ POSTCONDITIONS (output valid?)      │
        │ INVARIANTS (always true?)           │
        └─────────────────────────────────────┘
```

### Elementos

```c
/**
 * function_name - Brief description
 * @param1: Description and PRECONDITION
 * @param2: Description and PRECONDITION
 * 
 * PRECONDITIONS (must be true BEFORE call):
 *   - param1 != NULL
 *   - size > 0 && size < MAX_SIZE
 *   - object->state == INITIALIZED
 * 
 * POSTCONDITIONS (must be true AFTER call):
 *   - return value is allocated memory
 *   - *output != NULL
 *   - object->count increased
 * 
 * INVARIANTS (always true):
 *   - object->data always points to valid memory
 *   - object->size == actual allocated size
 *   - object->count >= 0
 * 
 * Returns: pointer to new memory, or NULL on error
 * 
 * Note: Caller must free returned pointer
 */
void *allocate_memory(size_t size, Object *object, void **output)
{
    // Verify PRECONDITIONS
    if (!object || !output)
        return NULL;
    if (size <= 0 || size > MAX_SIZE)
        return NULL;
    if (object->state != INITIALIZED)
        return NULL;
    
    // Do the work
    void *result = malloc(size);
    if (!result)
        return NULL;
    
    // Verify POSTCONDITIONS
    assert(result != NULL);
    assert(object->count_before < object->count);
    
    *output = result;
    return result;
}

// INVARIANTS are checked continuously throughout lifetime
```

### Aplicação em Arena

```c
/**
 * ft_arena_alloc - Allocate memory from arena
 * @chunk: Bytes to allocate (PRECONDITION: > 0)
 * @coliseu: Arena structure (PRECONDITION: state == ACTIVE)
 * 
 * PRECONDITIONS:
 *   - coliseu != NULL
 *   - coliseu->state == ARENA_ACTIVE
 *   - chunk > 0
 * 
 * POSTCONDITIONS:
 *   - returns valid memory pointer (or NULL on fail)
 *   - coliseu->region->begin increased
 *   - coliseu->region->avaliable decreased
 * 
 * INVARIANTS:
 *   - begin <= end always
 *   - avaliable >= 0 always
 *   - total_arenas matches actual chain length
 */
void *ft_arena_alloc(size_t chunk, t_coliseu *coliseu)
{
    // Validate PRECONDITIONS
    if (!coliseu)
        return NULL;
    if (coliseu->state != ARENA_ACTIVE)
        return NULL;
    if (chunk <= 0)
        return NULL;
    
    // Maintain INVARIANTS
    assert(coliseu->region->begin <= coliseu->region->end);
    assert(coliseu->region->avaliable >= 0);
    
    // ... allocation logic ...
    
    // Verify POSTCONDITIONS
    assert(coliseu->region->begin <= coliseu->region->end);
    assert(original_begin < coliseu->region->begin);
    
    return memory;
}
```

---

## Defensive Programming

### Definição e Princípios

**Referência:** Steve McConnell, "Code Complete" (2004), Cap. 8

**Princípios Fundamentais:**

1. **Never Trust Input**
   ```c
   // ✅ Defensive
   if (!ptr || size <= 0 || size > MAX)
       return error;
   ```

2. **Assume Bugs Exist**
   ```c
   // ✅ Usar assertions
   assert(pointer != NULL);
   assert(size >= 0);
   ```

3. **Fail Fast**
   ```c
   // ✅ Erro detectado cedo
   if (invalid_state)
       return -1;  // antes de processar
   ```

4. **Redundant Checks**
   ```c
   // ✅ Múltiplas camadas
   if (!resource)
       return;
   if (resource->cleaned)
       return;
   if (!resource->data)
       return;
   ```

### Técnicas Defensivas

```c
// ============================================================================
// 1. Input Validation
// ============================================================================

int process_data(const Data *data, int count) {
    // Validar cada parâmetro
    if (!data)
        return ERROR_NULL_POINTER;
    if (count <= 0 || count > MAX_COUNT)
        return ERROR_INVALID_COUNT;
    
    // Validar invariantes do input
    if (data->size != count * sizeof(int))
        return ERROR_CORRUPTED_DATA;
    
    return OK;
}

// ============================================================================
// 2. Assertions for Internal Logic
// ============================================================================

void internal_function(State *s) {
    // Precondition check
    assert(s != NULL);
    assert(s->initialized);
    
    // ... do work ...
    
    // Postcondition check
    assert(s->state == VALID_STATE);
}

// ============================================================================
// 3. Error Handling Patterns
// ============================================================================

// Pattern 1: Error code return
int read_file(const char *path, Buffer *buf) {
    if (!path || !buf)
        return E_NULL_PTR;
    
    FILE *fp = fopen(path, "r");
    if (!fp)
        return E_FILE_NOT_FOUND;
    
    // ... process ...
    
    if (fclose(fp) != 0)
        return E_FILE_CLOSE;
    
    return E_SUCCESS;
}

// Pattern 2: Goto cleanup (common in C)
int allocate_resources(void) {
    Resource *r1 = NULL;
    Resource *r2 = NULL;
    
    r1 = create_resource();
    if (!r1)
        goto cleanup;
    
    r2 = create_resource();
    if (!r2)
        goto cleanup;
    
    // ... use resources ...
    
    goto success;
    
cleanup:
    if (r1) destroy_resource(r1);
    if (r2) destroy_resource(r2);
    return ERROR;
    
success:
    if (r1) destroy_resource(r1);
    if (r2) destroy_resource(r2);
    return OK;
}

// ============================================================================
// 4. Defensive Copy Pattern
// ============================================================================

int safe_strcpy(char *dest, const char *src, size_t dest_size) {
    // Validate inputs
    if (!dest || !src || dest_size == 0)
        return ERROR;
    
    // Use safe version
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';  // Always null-terminate
    
    return OK;
}
```

### Aplicação em libft

```c
// ============================================================================
// Exemplo: ft_arena_destroy defensivo
// ============================================================================

void ft_arena_destroy(t_coliseu *coliseu) {
    // Layer 1: NULL check
    if (!coliseu)
        return;
    
    // Layer 2: State validation
    if (coliseu->state == ARENA_DESTROYED)
        return;  // Idempotent - safe to call again
    
    // Layer 3: Sanity check chain
    t_arena *current = coliseu->door;
    while (current) {
        // Bounds check
        if (current->begin > current->end) {
            fprintf(stderr, "PANIC: Corrupted arena detected\n");
            abort();
        }
        
        t_arena *next = current->next;
        free(current);
        current = next;
    }
    
    // Layer 4: Clear state
    coliseu->door = NULL;
    coliseu->region = NULL;
    coliseu->total_arenas = 0;
    coliseu->state = ARENA_DESTROYED;
}
```

---

## Referências Literárias Completas

### 📚 Livros Essenciais

#### 1. The C Programming Language (2ª ed.)
- **Autores:** Brian W. Kernighan, Dennis M. Ritchie
- **Publicação:** 1988
- **Seções Relevantes:**
  - Cap. 5: Pointers and Arrays
  - Cap. 6: Structures
  - Cap. 8: The Unix System Interface
- **Relevância para libft:** Fundamentals de C, memory management, file I/O

#### 2. Design Patterns: Elements of Reusable OO Software
- **Autores:** Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides (Gang of Four)
- **Publicação:** 1994
- **Seções Relevantes:**
  - Cap. 1: Introduction (Design Pattern Concepts)
  - Cap. 5: Behavioral Patterns → State Pattern (pp. 305-313)
  - Cap. 2: A Case Study → Observer Pattern
- **Relevância para libft:** State machine, factory patterns, observer pattern

#### 3. Code Complete (2ª ed.)
- **Autor:** Steve McConnell
- **Publicação:** 2004
- **Seções Relevantes:**
  - Cap. 5: Design in Construction
  - Cap. 8: Defensive Programming (pp. 203-260)
  - Cap. 31: Code-Tuning Strategies
- **Relevância para libft:** Defensive programming, code quality, debugging

#### 4. The Pragmatic Programmer (2ª ed.)
- **Autores:** David Thomas, Andrew Hunt
- **Publicação:** 2019
- **Seções Relevantes:**
  - Cap. 4: Pragmatic Paranoia
  - Cap. 8: Pragmatic Projects
- **Relevância para libft:** Best practices, error handling, code principles

#### 5. Object-Oriented Software Construction
- **Autor:** Bertrand Meyer
- **Publicação:** 1997
- **Seções Relevantes:**
  - Cap. 11: Contracts, Assertions and Exceptions
  - Cap. 12: Handling Abnormal Cases
- **Relevância para libft:** Design by Contract, invariants, preconditions

#### 6. The C++ Programming Language (4ª ed.)
- **Autor:** Bjarne Stroustrup
- **Publicação:** 2013
- **Seções Relevantes:**
  - Cap. 13: Exception Handling → RAII (pp. 369-420)
  - Cap. 14: Resource Management
- **Relevância para libft:** RAII pattern, scope-based cleanup (aplicável em C)

### 📋 Documentos Online

#### 1. RFC 7231: Hypertext Transfer Protocol (HTTP/1.1) Semantics
- **Link:** https://tools.ietf.org/html/rfc7231
- **Seção Relevante:** 4.2.1 Safe Methods, 4.2.2 Idempotent Methods
- **Conceito:** Definição formal de idempotência em HTTP
- **Aplicação:** Padrões de operações seguras

#### 2. RFC 7230: HTTP/1.1 Message Syntax
- **Seção Relevante:** Message Framing, Persistent Connections
- **Conceito:** Lifecycle management de conexões
- **Aplicação:** Cleanup de recursos de longa duração

#### 3. Rust Book - Ownership
- **Link:** https://doc.rust-lang.org/book/ch04-00-understanding-ownership.html
- **Seções Relevantes:**
  - Chapter 4: Understanding Ownership
  - Chapter 4.1: What is Ownership?
  - Chapter 4.2: References and Borrowing
  - Chapter 10.3: Lifetime Annotations
- **Conceito:** Ownership model em programação moderna
- **Aplicação:** Adaptar para C (manual ownership tracking)

#### 4. Wikipedia - Idempotence
- **Link:** https://en.wikipedia.org/wiki/Idempotence
- **Conteúdo:** Definição matemática, exemplos, aplicações
- **Aplicação:** Entender fundamentos teóricos

#### 5. cppreference.com - RAII
- **Link:** https://en.cppreference.com/w/cpp/memory/unique_ptr
- **Conceito:** Resource management patterns
- **Aplicação:** Entender RAII em C++, adaptar para C

### 🎓 Artigos e Publicações

#### 1. "Idempotency is not just a pretty HTTP word"
- **Autor:** Nick Craver
- **Conceito:** Importância prática de idempotência

#### 2. "What Every Programmer Should Know About Memory"
- **Autor:** Ulrich Drepper
- **Link:** https://people.freebsd.org/~lstewart/articles/cpumemory.pdf
- **Seções Relevantes:** Memory allocation, alignment, cache
- **Aplicação para libft:** Otimização de arena allocation

#### 3. "Safe C: How to Write Reliable and Secure C Programs"
- **Conteúdo:** Defensive programming techniques
- **Aplicação:** Memory safety, bounds checking

### 💾 Padrões Relacionados

#### 1. Singleton Pattern
- **Origem:** Gang of Four (1994)
- **Aplicação em libft:** Global arena manager (`ft_coliseu_manager`)
- **Benefício:** Garantir apenas uma instância de arenas globais

#### 2. Factory Pattern
- **Origem:** Gang of Four (1994)
- **Aplicação em libft:** `ft_coliseu_create()`, `ft_arena_init()`
- **Benefício:** Encapsular lógica de criação

#### 3. Strategy Pattern
- **Origem:** Gang of Four (1994)
- **Aplicação em libft:** Diferentes estratégias de alocação (POOL vs BLOCK)
- **Benefício:** Trocar comportamento em runtime

#### 4. Observer Pattern
- **Origem:** Gang of Four (1994)
- **Aplicação em libft:** Callbacks on state changes (futura)
- **Benefício:** Desacoplamento entre componentes

---

## 🎯 Matriz de Referências por Tema

| Tema | Livro | Cap/Seção | Artigo | RFC |
|------|-------|-----------|--------|-----|
| **State Machine** | Design Patterns, p.305 | - | - | - |
| **Idempotence** | - | - | RFC 7231 4.2.2 | RFC 7231 |
| **RAII** | C++ Lang, p.369 | Cap 13 | - | - |
| **Contracts** | Meyer OO, p.?? | Cap 11 | - | - |
| **Defensive** | Code Complete, p.203 | Cap 8 | - | - |
| **Memory** | K&R C, p.?? | Cap 5-6 | Drepper | - |
| **Ownership** | - | - | - | Rust Book |

---

## 📌 Como Usar Esta Referência

### Para Implementação de TASK_001:

1. **Leitura Inicial** → Design Patterns (State Pattern)
2. **Idempotência** → RFC 7231 + Code Complete
3. **Defensive Code** → Code Complete Cap. 8
4. **RAII (futuro)** → C++ Programming Language Cap. 13
5. **Ownership** → Rust Book Cap. 4

### Para Estudos Futuros:

1. **Memory Management** → Drepper PDF + K&R
2. **Advanced Patterns** → Design Patterns (completo)
3. **Modern C Practices** → The Pragmatic Programmer
4. **Correctness** → Meyer (Contracts)

---

**Última Atualização:** 6 de dezembro de 2025  
**Nível:** Intermediário a Avançado  
**Tempo de Leitura:** 4-6 horas
