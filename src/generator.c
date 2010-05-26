#include <stdio.h>
#include <stdlib.h>

#define TAM_BUFFER 2000000

int main(int argc, char ** argv)
{
  unsigned long i=0;
  unsigned long counter=0;
  unsigned long tam_buffer;
  char * buffer;
  char descricao[TAM_BUFFER];

  if(argc < 3){
    printf("usage: generator [size] [quantity]\n");
    return 1;
  }

  // le a descricao da sequencia
  while( (i<TAM_BUFFER) && ((descricao[i]=getchar()) != '\n'))
  {
    putchar(descricao[i]);
    i++;
  }
  putchar('\n');

  // armazena a sequencia na memoria
  i=0;
  buffer = (char *) malloc (sizeof(char)*TAM_BUFFER);
  while(  (buffer[i]=getchar() )!=EOF ) 
  {
    while((buffer[i]=='\n') && (buffer[i]!=EOF))
      buffer[i]=getchar();
    i++;
    counter++;
    if(counter > TAM_BUFFER)
    {
      counter=0;
      buffer = realloc(buffer,( (i+TAM_BUFFER)*sizeof(char)));
    }
  }
  tam_buffer = i;

  printf("\n %lu bases\n",tam_buffer);

  unsigned long j;
  unsigned long rand_i;
  unsigned int short_read_size;
  unsigned long short_read_quant;

  short_read_size = atoi(argv[1]);
  short_read_quant = atoi(argv[2]);

  for(i=0;i<short_read_quant;i++)
  {
    rand_i = rand() % (tam_buffer - short_read_size);
    printf("\n>> read[%lu]= %lu to %lu\n",i,rand_i,rand_i+short_read_size);
    for(j=0;j<short_read_size;j++)
      putchar(buffer[rand_i++]);

  }
  putchar('\n');
  return 0;
}
