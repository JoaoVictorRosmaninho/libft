#include "utils.h"


int main( void ) {

    ArrayList array = array_list_init();


    ft_printf("avaliable: %d\n", array.bucket_items->region->end - array.bucket_items->region->begin);
    ft_printf("chunk: %d\n", array.bucket_items->region->chunk);

    array_list_add(&array, "Joao victor");
    array_list_add(&array, "pedro henrique");
    array_list_add(&array, "Maria vitoria");
    
    array_list_print(&array);
    
    ft_printf("avaliable: %d\n", array.bucket_items->region->end - array.bucket_items->region->begin);
    
    ft_printf("chunk: %d\n", array.bucket_items->region->chunk);
    
    array_list_deinit(&array);
}