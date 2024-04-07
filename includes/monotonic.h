#ifndef MONOTONIC_H
# define MONOTONIC_H

typedef struct {
    size_t offset;
    size_t end;
    void* buffer;
    //future:
    //struct {
    //    t_coliseu coliseu;
    //    unsigned char coliseu_used;
    //};
} MonotonicBuffer;

MonotonicBuffer ft_monotonic_buffer_new(size_t size, void* buffer);
void            *ft_monotonic_alloc(size_t size, void* from);
#endif