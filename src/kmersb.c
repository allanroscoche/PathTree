#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv)
{
     PTree * p = NULL;
     char sequence[MAX_SEQ_LENGHT];
     char buff;
     unsigned int i,j;
     PKey k;

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

     j=0;
     sequence[j]=getchar();
     while( (j<MAX_SEQ_LENGHT) && (sequence[j] != EOF) && (sequence[j] != '>'))
     {
	  if((sequence[j] !='\n') && (sequence[j]!=' '))
	       j++;
	  sequence[j]=getchar();
     }
     sequence[j]='\0';

     //printf("%d:%s\n",j,sequence);

     k.size=j;
     memcpy(k.base,sequence,j);
     p=insert_tree(p,k);
     }
     print_tree(p);

     return 0;
}
