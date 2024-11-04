
#ifndef FTPRINTFH
#define FTPRINTFH


typedef enum {
    FLOAT,
    INTEGER,
    CHAR,
    STRING,
    LOWX,
    HIGHX,
    ELOW,  // cientific notation
    EHIGH, // cientific uppercase notation
    POINTER,
    TOBEPRINTED
} PrintfType;

typedef struct {
    char*       start_str;
    char*       end_str;
    PrintfType  type;
    int         precision;
    int         width;
    union {
        float   f;
        char    c;
        double  d;
        int     i;
        void*   p;  
    } content;
} PrintfInstruction;

#endif