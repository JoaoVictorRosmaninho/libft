


unsigned int ft_strlen(const char *S) {
  unsigned int size; 

  size = 0; 
  while (S[size])
    size++; 
  return (size); 
}
