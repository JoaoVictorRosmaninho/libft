

void *ft_memcpy(void *TO, void *FROM, unsigned int size) 
{
  unsigned int index; 

  index = 0; 
  while (index < size) 
  {
    *(((unsigned char *) TO) + index) =  *(((unsigned char *) FROM) + index);
    index++;
  }
  return (TO); 
}
