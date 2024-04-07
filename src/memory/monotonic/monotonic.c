#include "libft.h"

MonotonicBuffer ft_monotonic_buffer_new(size_t size, void* buffer) {
    return (MonotonicBuffer) {
        .offset       = 0,
        .end          = size,
        .buffer       = buffer
        //.coliseu_used = 0,
        //.coliseu      = { .door = NULL, .region = NULL, .size = ARENA_1KB }
    };
}

void *ft_monotonic_alloc(size_t size, void* from) {
    MonotonicBuffer* buffer = (MonotonicBuffer*) from;

    if ((buffer->offset + size) > buffer->end) {
        return (NULL);
        //  1 => estartegia alternativa de alocação
        //if (!buffer->coliseu_used) 
        //    buffer->coliseu_used = 1;
        //return ft_arena_alloc(size, ft_arena_alloc(size, &buffer->coliseu));
    }
    void* memory    = buffer + buffer->offset;
    buffer->offset += size;
    return memory;
}