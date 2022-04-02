
void *ft_memset(void *BLOCK, int C, unsigned int SIZE) {
  unsigned char value; 
  unsigned int index; 

  value = (unsigned char) C; 
  index = 0; 
  while (index < SIZE) {
    *(((unsigned char *) BLOCK) + index) = value; 
    index++;
  }
  return (BLOCK);
} 
