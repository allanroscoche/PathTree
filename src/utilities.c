#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 
   Aloca a estrutura da árvore de prefixos
*/
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
/*
  Aloca um nodo da árvore de prefixos
*/
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
/*
  Insere uma nova sequência na árvore de prefixos
*/
PNode * insert_node(PNode * no)
{
     if(no == NULL)
     {
       no = create_node();
     }
     no->counter++;

     return no;
}
/*
 Procura na árvore por uma sequencia
*/
PNode * search_tree(PTree * p, PKey chave)
{
     unsigned int i;
     PNode ** no;
     no =&(p->root);

     for(i=0; i < chave.size; i++)
     {
	  if(*no == NULL)
	       return NULL;

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
     
     return *no;
}
/*
  Insere uma chave na árvore
*/
PTree * insert_tree(PTree * p, PKey chave)
{
     unsigned int i;
     PNode ** no;
     PNode * pai;
     no =&(p->root);
     pai=NULL;
     
     for(i=0; i <= chave.size; i++)
     {
	  *no = insert_node(*no);
	  (*no)->pai=pai;
	  pai = *(no);
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
/*
  Imprime a árvore de prefixos
*/
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
/*
  Imprime os nodos
*/
void print_node(PNode *n)
{
     unsigned int i;
     unsigned int null_sons=0;
     PKey k;
     //printf("%d\n",n->counter);
     for(i=0;i<NUM_BASES;i++)
     {	       
       if(n->base[i]!=NULL)
       {
	  print_node(n->base[i]);
       }
       else
	    null_sons++;
       
     }
     if(null_sons == NUM_BASES)
     {
	  k = print_bases(n);
	  printf("%s",k.base);
	  printf(":%u\n",n->counter);
     }
	  
}


unsigned int sum,nodes;
void getkeys_node(PTree * t,PNode *n);

void getkeys_tree(PTree * t)
{
     if(t->root == NULL)
	  printf("Empty\n");
     else
     {
	  printf("tree:\n");
	  sum=0;
	  nodes=0;
	  getkeys_node(t,t->root);
     }
     printf(" sum:%d\n media:%d\n",sum, (sum/nodes));
}

void getkeys_node(PTree * t,PNode *n)
{
     unsigned int i;
     unsigned int null_sons=0;
     PKey k;
     unsigned char * contig;

     for(i=0;i<NUM_BASES;i++)
     {	       
       if(n->base[i]!=NULL)
       {
	    getkeys_node(t,n->base[i]);
       }
       else
	    null_sons++;
       
     }
     if(null_sons == NUM_BASES)
     {
	  nodes++;
	  sum+= n->counter;
	  k = print_bases(n);
	  contig = kmers(t,k);
	  printf("%s",contig);
	  printf(":%d \n",n->counter);
      if(contig != NULL)
        free(contig);
     }
	  
}
PNode * kmers_rec(PTree * t, PKey current_key, unsigned int size, unsigned int counter, unsigned char *);

unsigned char * kmers(PTree * t, PKey current_key)
{
     unsigned char * contig;

     contig = (unsigned char *)malloc((current_key.size)*sizeof(unsigned char));
     memcpy(contig,current_key.base,current_key.size);
     kmers_rec(t,current_key, 100,current_key.size-2,contig);

     return contig;
}

PNode * kmers_rec(PTree * t, PKey current_key, unsigned int size, unsigned int counter, unsigned char * contig)
{
  unsigned int i,j;
  unsigned int num_bases;
  PKey next_key;
  PNode * current_node;
  PNode * next_node;

  size--;
  counter++;
  // Copia a partir da segunda base sem o caracterer nulo do final
  memcpy(next_key.base,&(current_key.base[1]),current_key.size-1);
  next_key.size = current_key.size-1;
  
  current_node = search_tree(t,next_key);
  next_key.size++;
  
  if(current_node != NULL)
    {
      next_node=NULL;
      num_bases=0;
      for(i=0;i<NUM_BASES;i++)
        if( current_node->base[i]!=NULL)
          if(num_bases++ > 0)
            {
              //contig = (unsigned char *) realloc(contig,sizeof(unsigned char)*(counter+1));
              contig[counter-1]='\0';
              return current_node;
            }
      i=0;
      do {
        if(current_node->base[i]!=NULL)
          {
	    switch(i){ 
	    case 0:
	      next_key.base[current_key.size-1]='A';
	      break;
	    case 1:
	      next_key.base[current_key.size-1]='C';
	      break;
	    case 2:
	      next_key.base[current_key.size-1]='G';
	      break;
	    case 3:
	      next_key.base[current_key.size-1]='T';
	      break;
	    default:
	      next_key.base[current_key.size-1]='\0';
	      current_key.size--;
	      break;
	    }
	    contig = (unsigned char *) realloc(contig,sizeof(unsigned char)*(counter+1));
	    contig[counter]=next_key.base[current_key.size-1];
	    if(size > 0)
	      next_node = kmers_rec(t,next_key,size,counter,contig); // Recursão
	  }
      }while( (i++<NUM_BASES) && (next_node == NULL) );
      return next_node;
    }
  contig[counter-1]='\0';
  return current_node;
}


PKey print_bases(PNode * n)
{
     PKey k;
     char bases[MAX_SEQ_LENGHT];
     unsigned int size,i;
     PNode *filho;
          
     size=0;
     do {
	  filho = n;
	  n=n->pai;

	  for(i=0;i<NUM_BASES;i++)
	       if((n!=NULL) && (n->base[i] == filho))
	       {
		      switch(i)
		      {
		      case 0:
			   bases[size]='A';
			   break;
		      case 1:
			   bases[size]='C';
			   break;
		      case 2:
			   bases[size]='G';
			   break;
		      case 3:
			   bases[size]='T';
			   break;
		      }
		      size++;
	       }
	    
     }while(n != NULL);

     k.size=size;
     for(i=0;i<k.size;i++)
	  k.base[i]=bases[--size];
     k.base[i]='\0';
     

     return k;
}
/*
  Imprime uma chave
*/
void print_key(PKey k)
{
     int i;

     for(i=0;i<k.size;i++)
	  putchar(k.base[i]);

     putchar('\n');
}
