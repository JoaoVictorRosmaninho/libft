#ifndef ALLOCATOR_H
# define ALLOCATOR_H

typedef enum {
    MONOTONIC,
    ARENA
} AllocatorType;

typedef struct {
    void* (*alloc)(size_t size, void* from);
    void  (*free);
    void  (*release)(void* buffer, size_t length);
} Allocator;

typedef struct {
    AllocatorType type;
    void* (*alloc)(size_t size, void* from);
    void  (*free)(void* buffer);
    void  (*release)(void* buffer, size_t length);
} AllocatorContext;


Allocator allocator_new(AllocatorContext context);

#endif