#include "../../../includes/libft.h"


size_t hashs(Data* pair) {
    // Fnv Hash algorithm, the most simple

    size_t hash         = 0xcbf29ce484222325; // FNV_offset_basis

    unsigned char* byte = (unsigned char*) pair->content.s;

    for ( ; *byte; byte++) {
        hash *= 0x100000001b3; // FNV_prime
        hash ^= (size_t)*byte;  // xor with byte
    }

    return hash;
}

size_t hashd(Data* pair) {
    // Fnv Hash algorithm, the most simple

    size_t hash = 0xcbf29ce484222325; // FNV_offset_basis

    unsigned char* byte = (unsigned char*) &pair->content.d;

    for ( ; sizeof(pair->content.d); byte++) {
        hash *= 0x100000001b3; // FNV_prime
        hash ^= (size_t)byte;  // xor with byte
    }

    return hash;
}

size_t hashi(Data* pair) {
    // Fnv Hash algorithm, the most simple

    size_t hash = 0xcbf29ce484222325; // FNV_offset_basis

    unsigned char* byte = (unsigned char*) &pair->content.i;

    for ( ; sizeof(pair->content.i); byte++) {
        hash *= 0x100000001b3; // FNV_prime
        hash ^= (size_t)byte;  // xor with byte
    }

    return hash;
}

size_t hashui(Data* pair) {
    // Fnv Hash algorithm, the most simple

    size_t hash = 0xcbf29ce484222325; // FNV_offset_basis

    unsigned char* byte = (unsigned char*) &pair->content.ui;

    for ( ; sizeof(pair->content.ui); byte++) {
        hash *= 0x100000001b3; // FNV_prime
        hash ^= (size_t)byte;  // xor with byte
    }

    return hash;
}

size_t hashf(Data* pair) {
    // Fnv Hash algorithm, the most simple

    size_t hash = 0xcbf29ce484222325; // FNV_offset_basis

    unsigned char* byte = (unsigned char*) &pair->content.f;

    for ( ; sizeof(pair->content.f); byte++) {
        hash *= 0x100000001b3; // FNV_prime
        hash ^= (size_t)byte;  // xor with byte
    }

    return hash;

}
size_t hashc(Data* pair) {
    // Fnv Hash algorithm, the most simple

    size_t hash = 0xcbf29ce484222325; // FNV_offset_basis

    unsigned char* byte = (unsigned char*) &pair->content.c;

    for ( ; sizeof(pair->content.c); byte++) {
        hash *= 0x100000001b3; // FNV_prime
        hash ^= (size_t)byte;  // xor with byte
    }

    return hash;
}
