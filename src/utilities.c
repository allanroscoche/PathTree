#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>

void print_node(PNode *);

PTree * create_tree(PTree * t)
{

     if(t == NULL)
     {
	 t = (PTree *) malloc(sizeof(PTree));

	 if(t==NULL)
	 {
	      fprintf(stderr,"Cannot allocate tree\n");
	      exit(1);
	 }
     }

     t->root = NULL;

     return t;
}

PNode * create_node(void)
{
     PNode * no;
     unsigned int i;

     no = (PNode *) malloc(sizeof(PNode));

     no->counter=0;
     for(i=0;i<NUM_BASES;i++)
	  no->base[i]=NULL;

     return no;
}
PNode * insert_node(PNode * no)
{
     if(no == NULL)
     {
	  no = create_node();
     }
     no->counter++;

     return no;
}

PTree * insert_tree(PTree * p, PKey chave)
{
     unsigned int i;
     PNode ** no;
     no =&(p->root);
     
     for(i=0; i <= chave.size; i++)
     {
	  *no = insert_node(*no);
	  switch(chave.base[i])
	  {
	  case 'A':
	  case 'a':
	       no = &((*no)->base[A]);
	       break;

	  case 'C':
	  case 'c':
	       no = &((*no)->base[C]);
	       break;

	  case 'G':
	  case 'g':
	       no = &((*no)->base[G]);
	       break;

	  case 'T':
	  case 't':
	       no = &((*no)->base[T]);
	       break;

	  }
     }
     return p;
}

void print_tree(PTree * t)
{
     if(t->root == NULL)
	  printf("Empty\n");
     else
     {
	  printf("tree:\n");
	  print_node(t->root);
     }
     printf("\n");
}

void print_node(PNode *n)
{
     unsigned int i;
     unsigned int null_sons=0;
     //printf("%d\n",n->counter);
     for(i=0;i<NUM_BASES;i++)
     {	       
       if(n->base[i]!=NULL)
       {
	    switch(i)
	    {
	    case 0:
		 printf("A");
		 break;
	    case 1:
		 printf("C");
		 break;
	    case 2:
		 printf("G");
		 break;
	    case 3:
		 printf("T");
		 break;
	    }
	    print_node(n->base[i]);
       }
       else
	    null_sons++;
       
     }
     if(null_sons == NUM_BASES)
	  printf(":%u\n",n->counter);
	  
}
