#include "utils.h"

uint8_t  cmp(void* a, void* b) {
     int r = ft_strncmp((char*)a, (char*)b, ft_strlen((const char*) a));

     if (r != 0) return 0;

     return 1;
 };


Test(size, ft_liked_list_test)
{
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_8KB
    };

    t_list* lst = ft_lstnew(&coliseu);

    ft_lstadd_back(lst, ft_lstnew_node(mk_string_content("joao victor", &coliseu), STRING, &coliseu));
    ft_lstadd_back(lst, ft_lstnew_node(mk_string_content("abacaxi", &coliseu), STRING, &coliseu));
    ft_lstadd_back(lst, ft_lstnew_node(mk_string_content("limao", &coliseu), STRING, &coliseu));

    cr_expect(lst->size == 3, "expect that list have correct size");

    ft_arena_destroy(&coliseu);
}



Test(includes, ft_liked_list_test)
{
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_8KB
    };

    t_list* lst = ft_lstnew(&coliseu);


    ft_lstadd_back(lst, ft_lstnew_node("joao victor", STRING, &coliseu));
    ft_lstadd_back(lst, ft_lstnew_node("abacaxi", STRING, &coliseu));
    ft_lstadd_back(lst, ft_lstnew_node("limao", STRING, &coliseu));

    t_node* r = ft_lst_include(lst, "abacaxi", cmp);
    t_node* r2 = ft_lst_include(lst, "limao", cmp);
    t_node* r3 = ft_lst_include(lst, "joao victor", cmp);
    t_node* r4 = ft_lst_include(lst, "laranja", cmp);


    cr_expect( r != NULL, "expect that list have correct size");
    cr_expect( r2 != NULL, "expect that list have correct size");
    cr_expect( r3 != NULL, "expect that list have correct size");
    cr_expect( r4 == NULL, "expect that list have correct size");

    ft_arena_destroy(&coliseu);
}

Test(includes, ft_linkest_search_and_remove) {
        t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_8KB
    };

    t_list* lst = ft_lstnew(&coliseu);


    ft_lstadd_back(lst, ft_lstnew_node("joao victor", STRING, &coliseu));
    ft_lstadd_back(lst, ft_lstnew_node("abacaxi", STRING, &coliseu));
    ft_lstadd_back(lst, ft_lstnew_node("limao", STRING, &coliseu));


    cr_expect(lst->size == 3, "right size");

    ft_lst_search_and_pop(lst, "joao victor", cmp);
    cr_expect( lst->size == 2, "expect to remove");

    ft_lst_search_and_pop(lst, "abacaxi", cmp);
    cr_expect( lst->size == 1, "expect to remove");

    ft_lst_search_and_pop(lst, "laranja", cmp);
    cr_expect( lst->size == 1, "expect to not remove");

    ft_lst_search_and_pop(lst, "limao", cmp);
    cr_expect( lst->size == 0, "expect to remove");

    ft_arena_destroy(&coliseu);
}


Test(array_list, add_new_item) {

    ArrayList al = array_list_init( ARENA_16KB );


    array_list_add_int(&al, 10);

    cr_expect( al.index == 1, "expect add one element");

    array_list_deinit(&al);

}

Test(array_list, remove_new_item) {

    ArrayList al = array_list_init( ARENA_16KB );


    array_list_add_int(&al, 10);

    array_list_pop(&al);

    cr_expect( al.index == 0, "expect to remove one element");

    array_list_deinit(&al);
}

Test(array_list, insert_new_item) {

    ArrayList al = array_list_init( ARENA_16KB );


    array_list_add_int(&al, 10);

    array_list_add_int_on(&al, 0, 20);

    cr_expect( al.index == 1, "expect to remove one element");
    cr_expect( array_list_getitem(&al, 0)->content.i == 20, "expect to remove one element");

    array_list_deinit(&al);
}

