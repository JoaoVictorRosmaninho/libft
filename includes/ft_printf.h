
#ifndef FTPRINTFH
#define FTPRINTFH

typedef enum {
    PDIGIT = 1,
    PUDIGIT,
    PUOCTAL,
    PLOWX,
    PHIGHX,
    PLOWF,
    PHIGHF,
    PELOW,  // cientific notation
    PEHIGH,  // cientific uppercase notation
    PSHORLOWREPR,
    PSHORHIGHREPR,
    PHEXFLOW,
    PHEXFHIGH,
    PCHAR,
    PSTRING,
    PPOINTER,
    PNOTHING,
    PPERCENT,
    TOBEPRINTED
} PrintfType;

typedef struct {
    PrintfType        type;
    int               precision;
    int               width;
    t_coliseu*        buffer;
    union {
        char          c;
        char*         p;  
    } content;
} PrintfInstruction;


typedef struct {
    t_coliseu* buffer;
    char*     content;
    size_t    size;
} PrintfStringBuilder;

#endif