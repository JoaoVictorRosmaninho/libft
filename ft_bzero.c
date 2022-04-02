
void *ft_bzero(void *BLOCK, unsigned int SIZE) {
  unsigned int index; 

  index = 0; 
  while (index < SIZE) {
    *(((unsigned char *) BLOCK) + index) = 0; 
    index++;
  }
  return (BLOCK);
} 
