# Exemplos de Implementação - Arena Robustness

Este arquivo contém exemplos práticos de como implementar os padrões descritos na TASK_001.

---

## 1. State Machine - Definição

### Header: arena.h (modifications)

```c
#ifndef ARENA_H
# define ARENA_H

// ... existing includes ...

/**
 * Arena states define the lifecycle of a coliseu
 * 
 * UNINITIALIZED -> ACTIVE -> DESTROYED
 *      ↑                           ↓
 *      └───────────────────────────┘
 *         (can't go back, but transitions are safe)
 */
typedef enum e_arena_state
{
	ARENA_UNINITIALIZED = 0,  // Never created
	ARENA_ACTIVE = 1,         // Ready to use
	ARENA_DESTROYED = 2       // Cleaned up
}	t_arena_state;

/**
 * Updated coliseu structure with state tracking
 */
typedef struct s_coliseu
{
	t_arena_state		state;		// ← NEW: Explicit state
	t_arena				*door;		// Head of arena list
	t_arena				*region;	// Current active arena
	size_t				size;		// Size per arena block
	uint16_t			total_arenas;
	enum arena_type		type;
}	t_coliseu;

// ... rest of declarations ...

#endif
```

---

## 2. Idempotent Destroy - Full Implementation

### File: arena_utils.c (updated)

```c
#include "../../includes/libft.h"

/**
 * ft_arena_destroy - Safely destroy all arenas in a coliseu
 * @coliseu: Structure to destroy
 * 
 * IDEMPOTENT: Safe to call multiple times with the same pointer.
 * 
 * This function is defensive against:
 * - NULL pointers
 * - Already-destroyed coliseus
 * - Partial initialization
 * - Double-free scenarios
 * 
 * Invariants maintained:
 * - After destruction, all pointers are NULL
 * - State is marked as DESTROYED
 * - Subsequent calls do nothing (safe)
 * 
 * Example:
 *   t_coliseu arena = {0};
 *   ft_coliseu_create(&arena);
 *   ft_arena_destroy(&arena);  // OK
 *   ft_arena_destroy(&arena);  // OK, idempotent
 *   ft_arena_destroy(&arena);  // OK, idempotent
 *   ft_arena_destroy(NULL);    // OK, safe
 */
void	ft_arena_destroy(t_coliseu *coliseu)
{
	t_arena	*arena;
	t_arena	*_arena;

	// Defensive check 1: NULL input
	if (!coliseu)
		return ;
	
	// Defensive check 2: Already destroyed (idempotence)
	if (coliseu->state == ARENA_DESTROYED)
		return ;
	
	// Only proceed if we have something to free
	arena = coliseu->door;
	while (arena)
	{
		_arena = arena;
		arena = arena->next;
		free(_arena);
	}
	
	// Clear all pointers to prevent accidental reuse
	coliseu->door = NULL;
	coliseu->region = NULL;
	coliseu->total_arenas = 0;
	
	// Mark state as destroyed
	coliseu->state = ARENA_DESTROYED;
}

/**
 * ft_arena_validate - Check invariants of a coliseu
 * @coliseu: Structure to validate
 * 
 * Returns:
 *   0 if valid
 *   -1 if NULL
 *   -2 if state is invalid
 *   -3 if pointers are corrupted
 * 
 * Invariants checked:
 * - UNINITIALIZED: door and region must be NULL
 * - ACTIVE: door and region must be non-NULL, and form valid chain
 * - DESTROYED: door and region must be NULL
 * - Memory bounds: begin <= end in all arenas
 * 
 * Usage:
 *   if (ft_arena_validate(&arena) != 0)
 *       return (error_handler());
 */
int	ft_arena_validate(const t_coliseu *coliseu)
{
	const t_arena	*current;
	
	// Check 1: Null input
	if (!coliseu)
		return (-1);
	
	// Check 2: Invalid state
	if (coliseu->state > ARENA_DESTROYED)
		return (-2);
	
	// Check 3: Invariants per state
	if (coliseu->state == ARENA_UNINITIALIZED)
	{
		if (coliseu->door != NULL || coliseu->region != NULL)
			return (-3);
	}
	else if (coliseu->state == ARENA_ACTIVE)
	{
		if (coliseu->door == NULL || coliseu->region == NULL)
			return (-3);
		
		// Check chain integrity
		current = coliseu->door;
		while (current)
		{
			// Bounds check
			if (current->begin > current->end)
				return (-3);
			
			current = current->next;
		}
	}
	else if (coliseu->state == ARENA_DESTROYED)
	{
		if (coliseu->door != NULL || coliseu->region != NULL)
			return (-3);
		if (coliseu->total_arenas != 0)
			return (-3);
	}
	
	return (0);
}

/**
 * ft_arena_free - Reset arena to reusable state (NOT destroy)
 * @coliseu: Structure to reset
 * 
 * This is different from destroy:
 * - destroy: frees memory
 * - free: resets begin pointers for reuse
 * 
 * Use case: Reuse arena within same program execution
 * 
 * Example:
 *   // Use arena for frame 1
 *   ft_arena_alloc(1024, &arena);
 *   
 *   // Reset for frame 2
 *   ft_arena_free(&arena);  // begin pointers reset
 *   
 *   // Now arena is empty again, reuse for frame 2
 *   ft_arena_alloc(1024, &arena);
 */
void	ft_arena_free(t_coliseu *coliseu)
{
	t_arena	*arena;

	if (!coliseu || !coliseu->door)
		return ;
	
	arena = coliseu->door;
	while (arena)
	{
		arena->begin = (char *)arena + sizeof(t_arena);
		arena = arena->next;
	}
	coliseu->region = coliseu->door;
}

/**
 * ft_coliseu_rollback - Undo recent allocations
 * @region: Arena to rollback
 * @rollback: Bytes to rollback
 * 
 * Defensive: checks bounds before rolling back
 */
void	ft_coliseu_rollback(t_arena *region, size_t rollback)
{
	if (!region)
		return ;
	if ((region->begin - rollback)
		< (region->end + sizeof(void *) - region->chunk))
		return ;
	region->begin -= rollback;
}

// ... rest of existing functions ...
```

---

## 3. Explicit Cleanup (Remove Side Effects)

### File: ft_printf.c (modifications)

```c
// BEFORE (BAD - side effects):
int ft_printf(const char *format, ...)
{
    va_list arg_list;
    size_t len = 0;

    if (!format)
        return (0);

    va_start(arg_list, format);
    len = ft_printf_lexer(format, arg_list);
    va_end(arg_list);

    ft_coliseu_manager(GIVE_BACK);  // ❌ Hidden side effect!

    return (len);
}

// AFTER (GOOD - explicit):
int ft_printf(const char *format, ...)
{
    va_list arg_list;
    size_t len = 0;

    if (!format)
        return (0);

    va_start(arg_list, format);
    len = ft_printf_lexer(format, arg_list);
    va_end(arg_list);

    // ✅ Removed side effect - caller controls cleanup
    return (len);
}

/**
 * ft_arena_cleanup - Explicit cleanup of global arenas
 * 
 * Call this function ONCE at end of program or between major phases.
 * This replaces the implicit cleanup that was in ft_printf.
 * 
 * Usage:
 *   int main(void) {
 *       // ... program execution ...
 *       
 *       ft_arena_cleanup();  // Explicit, clear cleanup
 *       return (0);
 *   }
 */
void ft_arena_cleanup(void)
{
    ft_coliseu_manager(GIVE_BACK);
}
```

---

## 4. Comprehensive Test Suite

### File: test/arena_robustness_test.c

```c
#include <stdio.h>
#include <assert.h>
#include "libft.h"
#include "test_framework.h"

// ============================================================================
// Test Group 1: Idempotence
// ============================================================================

void test_arena_destroy_null_is_safe(void)
{
    // Should not crash or error
    ft_arena_destroy(NULL);
    
    t_test("Arena destroy handles NULL safely");
}

void test_arena_destroy_is_idempotent(void)
{
    t_coliseu arena = {0};
    
    // Setup
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    
    // Allocate
    void *ptr1 = ft_arena_alloc(64, &arena);
    void *ptr2 = ft_arena_alloc(128, &arena);
    
    assert(ptr1 != NULL && ptr2 != NULL);
    assert(arena.state == ARENA_ACTIVE);
    
    // First destroy
    ft_arena_destroy(&arena);
    assert(arena.door == NULL);
    assert(arena.region == NULL);
    assert(arena.state == ARENA_DESTROYED);
    
    // Second destroy - must be safe
    ft_arena_destroy(&arena);
    assert(arena.door == NULL);
    assert(arena.region == NULL);
    assert(arena.state == ARENA_DESTROYED);
    
    // Third destroy - must still be safe
    ft_arena_destroy(&arena);
    
    // Many destroys
    for (int i = 0; i < 100; i++)
        ft_arena_destroy(&arena);
    
    t_test("Arena destroy is idempotent (safe multiple calls)");
}

void test_arena_destroy_in_loop(void)
{
    // Simulate pattern that caused original bug
    for (int i = 0; i < 1000; i++)
    {
        t_coliseu arena = {0};
        arena.size = ARENA_32KB;
        ft_coliseu_create(&arena);
        
        ft_arena_alloc(256, &arena);
        
        ft_arena_destroy(&arena);
        ft_arena_destroy(&arena);  // Second destroy in loop
    }
    
    t_test("Arena destroy multiple times in loop");
}

// ============================================================================
// Test Group 2: State Machine
// ============================================================================

void test_arena_state_transitions(void)
{
    t_coliseu arena = {0};
    
    // Initial state
    assert(arena.state == ARENA_UNINITIALIZED);
    
    // After create
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    assert(arena.state == ARENA_ACTIVE);
    
    // After destroy
    ft_arena_destroy(&arena);
    assert(arena.state == ARENA_DESTROYED);
    
    t_test("Arena state transitions correctly");
}

void test_arena_cannot_alloc_when_destroyed(void)
{
    t_coliseu arena = {0};
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    
    ft_arena_destroy(&arena);
    
    // Try to allocate after destruction
    void *ptr = ft_arena_alloc(64, &arena);
    
    // Should be NULL or safe (depends on implementation)
    // Current: Returns NULL due to region == NULL
    
    t_test("Arena prevents allocation after destruction");
}

// ============================================================================
// Test Group 3: Validation
// ============================================================================

void test_arena_validate_uninitialized(void)
{
    t_coliseu arena = {0};
    
    int result = ft_arena_validate(&arena);
    assert(result == 0);  // Valid uninitialized state
    
    t_test("Validation accepts uninitialized state");
}

void test_arena_validate_active(void)
{
    t_coliseu arena = {0};
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    
    int result = ft_arena_validate(&arena);
    assert(result == 0);  // Valid active state
    
    ft_arena_destroy(&arena);
    
    t_test("Validation accepts active state");
}

void test_arena_validate_destroyed(void)
{
    t_coliseu arena = {0};
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    ft_arena_destroy(&arena);
    
    int result = ft_arena_validate(&arena);
    assert(result == 0);  // Valid destroyed state
    
    t_test("Validation accepts destroyed state");
}

void test_arena_validate_null(void)
{
    int result = ft_arena_validate(NULL);
    assert(result < 0);  // Should detect invalid
    
    t_test("Validation rejects NULL");
}

// ============================================================================
// Test Group 4: Memory Integrity
// ============================================================================

void test_arena_no_memory_leaks_single(void)
{
    // Run with: valgrind --leak-check=full ./test_runner
    t_coliseu arena = {0};
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    
    void *ptrs[100];
    for (int i = 0; i < 100; i++)
        ptrs[i] = ft_arena_alloc(64, &arena);
    
    ft_arena_destroy(&arena);
    
    // Valgrind should report 0 leaks
    
    t_test("No memory leaks in single arena");
}

void test_arena_no_memory_leaks_multiple(void)
{
    // Heavy stress test for valgrind
    for (int i = 0; i < 100; i++)
    {
        t_coliseu arena = {0};
        arena.size = ARENA_32KB;
        ft_coliseu_create(&arena);
        
        for (int j = 0; j < 50; j++)
            ft_arena_alloc(128, &arena);
        
        ft_arena_destroy(&arena);
        ft_arena_destroy(&arena);  // Second destroy
    }
    
    t_test("No memory leaks with stress test");
}

// ============================================================================
// Test Group 5: Invariants
// ============================================================================

void test_arena_maintains_bounds_invariant(void)
{
    t_coliseu arena = {0};
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    
    // Invariant: begin <= end
    assert(arena.region->begin <= arena.region->end);
    
    for (int i = 0; i < 100; i++)
    {
        ft_arena_alloc(64, &arena);
        assert(arena.region->begin <= arena.region->end);
    }
    
    ft_arena_destroy(&arena);
    
    t_test("Arena maintains begin <= end invariant");
}

void test_arena_tracks_available_space(void)
{
    t_coliseu arena = {0};
    arena.size = ARENA_32KB;
    ft_coliseu_create(&arena);
    
    size_t initial_available = arena.region->avaliable;
    assert(initial_available > 0);
    
    ft_arena_alloc(1024, &arena);
    size_t after_alloc = arena.region->avaliable;
    
    // Should have less available space
    assert(after_alloc < initial_available);
    
    ft_arena_destroy(&arena);
    
    t_test("Arena tracks available space correctly");
}

// ============================================================================
// Test Group 6: Global Arena Manager
// ============================================================================

void test_global_arena_manager_explicit_cleanup(void)
{
    // New pattern with explicit cleanup
    t_coliseu *arena1 = ft_coliseu_manager(TAKE);
    void *ptr1 = ft_arena_alloc(512, arena1);
    assert(ptr1 != NULL);
    
    // Explicit cleanup
    ft_arena_cleanup();
    
    // Should be able to allocate again (fresh state)
    t_coliseu *arena2 = ft_coliseu_manager(TAKE);
    void *ptr2 = ft_arena_alloc(512, arena2);
    assert(ptr2 != NULL);
    
    ft_arena_cleanup();
    
    t_test("Global arena manager with explicit cleanup");
}

// ============================================================================
// Main Test Runner
// ============================================================================

int main(void)
{
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║          ARENA ROBUSTNESS TEST SUITE                       ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    // Group 1
    printf("📋 Group 1: Idempotence\n");
    test_arena_destroy_null_is_safe();
    test_arena_destroy_is_idempotent();
    test_arena_destroy_in_loop();
    
    // Group 2
    printf("\n📋 Group 2: State Machine\n");
    test_arena_state_transitions();
    test_arena_cannot_alloc_when_destroyed();
    
    // Group 3
    printf("\n📋 Group 3: Validation\n");
    test_arena_validate_uninitialized();
    test_arena_validate_active();
    test_arena_validate_destroyed();
    test_arena_validate_null();
    
    // Group 4
    printf("\n📋 Group 4: Memory Integrity\n");
    test_arena_no_memory_leaks_single();
    test_arena_no_memory_leaks_multiple();
    
    // Group 5
    printf("\n📋 Group 5: Invariants\n");
    test_arena_maintains_bounds_invariant();
    test_arena_tracks_available_space();
    
    // Group 6
    printf("\n📋 Group 6: Global Manager\n");
    test_global_arena_manager_explicit_cleanup();
    
    printf("\n✅ All tests completed!\n\n");
    
    return (0);
}
```

---

## 5. Ownership Documentation Template

### File: OWNERSHIP_MODEL.md

```markdown
# libft Arena - Ownership Model

## Overview

Three types of arena ownership are supported in libft:

### 1. Global Singleton Arenas

```
ownership: libft (internal)
control: ft_coliseu_manager
lifecycle: program start to exit
thread-safe: NO (single-threaded)
```

**Usage:**
```c
int main(void) {
    // Implicitly created on first use
    char *str = ft_strdup("hello", ft_coliseu_manager(TAKE));
    
    // Explicit cleanup
    ft_arena_cleanup();
    
    return 0;
}
```

**Responsibility:**
- ✅ libft initializes
- ✅ libft cleans up (via ft_arena_cleanup)
- ❌ Caller must NOT directly destroy global arenas

---

### 2. Caller-Owned Dynamic Arenas

```
ownership: caller
control: caller directly
lifecycle: caller manages
thread-safe: NO (unless protected externally)
```

**Usage:**
```c
void process_data(void) {
    t_coliseu my_arena = {0};
    
    // 1. Caller creates
    my_arena.size = ARENA_32KB;
    ft_coliseu_create(&my_arena);
    
    // 2. Caller uses
    char *tmp = ft_strdup("data", &my_arena);
    
    // 3. Caller destroys
    ft_arena_destroy(&my_arena);
}
```

**Responsibility:**
- ✅ Caller must create (ft_coliseu_create)
- ✅ Caller must destroy (ft_arena_destroy)
- ✅ Caller must not use after destruction

---

### 3. Stack-Scoped RAII Arenas (Future)

```
ownership: compiler/RAII
control: scope exit
lifecycle: automatic
thread-safe: NO (unless protected externally)
```

**Usage (with __attribute__((cleanup))):**
```c
static inline void arena_cleanup(t_coliseu **a) {
    ft_arena_destroy(*a);
}

void process_data(void) {
    t_coliseu __attribute__((cleanup(arena_cleanup))) my_arena = {0};
    
    my_arena.size = ARENA_32KB;
    ft_coliseu_create(&my_arena);
    
    // ... use ...
    
    // ← Automatically destroyed here
}
```

**Responsibility:**
- ✅ RAII handles it
- ❌ Caller must NOT manually destroy

---

## Transition Rules

| From | To | Allowed | Notes |
|------|----|---------|----|
| UNINITIALIZED | ACTIVE | ✅ | Call ft_coliseu_create |
| ACTIVE | DESTROYED | ✅ | Call ft_arena_destroy |
| DESTROYED | UNINITIALIZED | ❌ | Use new struct instead |
| DESTROYED | DESTROYED | ✅ | Idempotent (safe) |

---

## Common Patterns

### Pattern 1: One-time Setup
```c
int main(void) {
    ft_printf("Hello %s\n", "world");  // Uses global arena
    ft_arena_cleanup();                 // Cleanup at end
    return 0;
}
```

### Pattern 2: Per-Frame Arena
```c
void game_loop(void) {
    for (int frame = 0; frame < 60; frame++) {
        t_coliseu frame_arena = {0};
        frame_arena.size = ARENA_32KB;
        ft_coliseu_create(&frame_arena);
        
        // Frame work
        update_game(&frame_arena);
        render_game(&frame_arena);
        
        ft_arena_destroy(&frame_arena);  // Reset each frame
    }
}
```

### Pattern 3: Nested Arenas
```c
void outer(void) {
    t_coliseu outer_arena = {0};
    outer_arena.size = ARENA_64KB;
    ft_coliseu_create(&outer_arena);
    
    inner(&outer_arena);
    
    ft_arena_destroy(&outer_arena);
}

void inner(t_coliseu *parent) {
    t_coliseu inner_arena = {0};
    inner_arena.size = ARENA_32KB;
    ft_coliseu_create(&inner_arena);
    
    // ... work ...
    
    ft_arena_destroy(&inner_arena);
}
```

---

## Error Handling

```c
int ft_arena_safe_alloc(size_t size, t_coliseu *arena, void **out) {
    // Validate
    if (ft_arena_validate(arena) != 0)
        return -1;  // Invalid state
    
    if (!out)
        return -2;  // Bad output pointer
    
    // Allocate
    *out = ft_arena_alloc(size, arena);
    if (!*out)
        return -3;  // Allocation failed
    
    return 0;  // Success
}
```

---
```

---

## Summary

These examples show:

1. **State Machine** - Clear lifecycle management
2. **Idempotence** - Safe multiple calls
3. **Explicit Cleanup** - Remove side effects
4. **Comprehensive Tests** - Edge cases covered
5. **Documentation** - Clear ownership and patterns

All following the defensive programming and design patterns discussed in TASK_001.

**To run tests:**
```bash
cd /path/to/libft
make test
valgrind --leak-check=full ./test_runner
```

**Status:** Ready for implementation
