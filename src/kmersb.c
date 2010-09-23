#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main(int argc, char ** argv)
{
  PTree * p = NULL;
  char sequence[MAX_SEQ_LENGHT];
  char buff;
  unsigned int i;
  PKey k;
  PKey * buffer_k;
  unsigned char * contig;
  
  p = create_tree(p);
  
  while( (buff=getchar()) != EOF)
    {
	  while( (buff == '\n') && (buff!=EOF)){
        buff=getchar();
	  }
	  if(buff == '>')
        {
          do {
		    buff = getchar();
          }while( (buff != '\n') && (buff != EOF));
        }
      
	  i=0;
	  sequence[i]=getchar();
	  while( (i<MAX_SEQ_LENGHT) && (sequence[i] != EOF) && (sequence[i] != '>'))
        {
          if((sequence[i] !='\n') && (sequence[i]!=' '))
		    i++;
          sequence[i]=getchar();
        }
	  sequence[i]='\0';
	  
	  k.size=i;
	  memcpy(k.base,sequence,i);
	  p=insert_tree(p,k);
    }
  
     
  //contig = kmers(p,k);
  //printf("%s\n\n",contig);
  
  //getkeys_tree(p);
  
  //print_tree(p);
  
  return 0;
}
