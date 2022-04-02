
int ft_isalpha(int c);
int ft_isdigit(int C);

int ft_isalnum(int C) {
  return (ft_isdigit(C) || ft_isalpha(C));   
}

