#include "utils.h"

Test(parse_raw_strings, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("Ola mundo!!");
    
    cr_assert_stdout_eq_str("Ola mundo!!");
}

Test(parse_long_raw_strings, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum ac euismod eros. Nulla eget lacus condimentum, pharetra sem at, consectetur lacus. Donec hendrerit, odio vitae fermentum venenatis, lectus leo mollis justo, quis dapibus nunc risus sit amet odio. Quisque non euismod tortor, vitae imperdiet enim.");
    
    cr_assert_stdout_eq_str("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum ac euismod eros. Nulla eget lacus condimentum, pharetra sem at, consectetur lacus. Donec hendrerit, odio vitae fermentum venenatis, lectus leo mollis justo, quis dapibus nunc risus sit amet odio. Quisque non euismod tortor, vitae imperdiet enim.");
}

Test(parse_raw_strings_with_percent, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("Ola mundo %% !!");
    
    cr_assert_stdout_eq_str("Ola mundo % !!");
}

Test(parse_raw_string_and_iterpolate_char, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("char %c is C", 'C');

    cr_assert_stdout_eq_str("char C is C");
}

Test(parse_raw_string_and_iterpolate_string, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("string passed is: %s", "testado string interpolada");

    cr_assert_stdout_eq_str("string passed is: testado string interpolada");
}

Test(parse_raw_string_and_iterpolate_int, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("number passed is: %d", 5);

    cr_assert_stdout_eq_str("number passed is: 5");
}

Test(parse_raw_string_and_iterpolate_uint, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("number passed is: %u", 5);

    cr_assert_stdout_eq_str("number passed is: 5");
}

Test(parse_raw_string_and_iterpolate_large_int, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("number passed is: %d", 51236546);

    cr_assert_stdout_eq_str("number passed is: 51236546");
}

Test(parse_raw_string_and_iterpolate_large_uint, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("number passed is: %u", 51236546);

    cr_assert_stdout_eq_str("number passed is: 51236546");
}

Test(parse_raw_string_and_iterpolate_large_negative_int, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("number passed is: %d", -15);

    cr_assert_stdout_eq_str("number passed is: -15");
}

Test(parse_raw_string_and_iterpolate_float, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("number passed is: %f", 5.25);

    cr_assert_stdout_eq_str("number passed is: 5.250000");
}

Test(parse_raw_string_and_iterpolate_float_with_decimal_count, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("number passed is: %.2f", 5.25);

    cr_assert_stdout_eq_str("number passed is: 5.25");
}

Test(parse_raw_string_and_iterpolate_string_with_spaces, ft_printf_lexer, .init = cr_redirect_stdout) {
    ft_printf("number passed is: %2s", "abelha");

    cr_assert_stdout_eq_str("number passed is: abelha");
}
