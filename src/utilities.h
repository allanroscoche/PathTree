#define NUM_BASES 4
#define MAX_SEQ_LENGHT 30

typedef enum Base
{ A, C, G, T } Base;

typedef struct PKey
{
     char base[MAX_SEQ_LENGHT];
     unsigned int size;
} PKey;

typedef struct PNode
{
     unsigned int counter;
     struct PNode *base[NUM_BASES];
} PNode;

typedef struct PTree
{
     PNode * root;
} PTree;

PTree * create_tree(PTree *);             
PTree * insert_tree(PTree *, PKey );
void print_tree(PTree *);
