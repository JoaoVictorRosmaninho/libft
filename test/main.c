#include "utils.h"

/*
uint8_t  cmp(void* a, void* b) {
     int r = ft_strncmp((char*)a, (char*)b, ft_strlen((const char*) a));

     if (r != 0) return 0;

     return 1;
 };

 int main(void) {
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_8KB
    };

    t_list* lst = ft_lstnew(&coliseu);


    ft_lstadd_back(lst, ft_lstnew_node("joao victor", STRING, &coliseu));
    ft_lstadd_back(lst, ft_lstnew_node("abacaxi", STRING, &coliseu));
    ft_lstadd_back(lst, ft_lstnew_node("limao", STRING, &coliseu));


    //cr_expect(lst->size == 3, "right size");

    ft_lst_search_and_pop(lst, "joao victor", cmp);

    ft_lst_search_and_pop(lst, "abacaxi", cmp);
    
    ft_lst_search_and_pop(lst, "limao", cmp);

    //ft_lst_search_and_pop(lst, "laranja", cmp);



    printf("SIZE: %d\n", lst->size);

    ft_arena_destroy(&coliseu);
 }
 */



int main( void ) {
    printf("number passed is: %15s\n", "abelha");
    ft_printf("number passed is: %15s\n", "abelha");
}