# define ALPHA_MASC_INIT  65      
# define ALPHA_MASC_END   90      
# define ALPHA_MIN_INIT   97      
# define ALPHA_MIN_END    122   

int ft_isalpha(int c)
{
  return (
        (c >= ALPHA_MASC_INIT && c <= ALPHA_MASC_END) 
        || (c >= ALPHA_MIN_INIT && c <= ALPHA_MIN_END)
        );
}
