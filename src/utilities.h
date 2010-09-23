#define NUM_BASES 4
#define MAX_SEQ_LENGHT 35

typedef enum Base
{ A, C, G, T } Base;

typedef struct PKey
{
     char base[MAX_SEQ_LENGHT];
     unsigned int size;
} PKey;

typedef struct PNode
{
     int counter;
     struct PNode *base[NUM_BASES];
     struct PNode * pai;
} PNode;

typedef struct PTree
{
     PNode * root;
} PTree;

struct nodes_index
{
     unsigned int counter;
     int number;
};

PTree * create_tree(PTree *);             
PTree * insert_tree(PTree *, PKey );
void print_tree(PTree *);
PNode * search_tree(PTree *, PKey );
void print_key(PKey );
PKey print_bases(PNode *);
void print_node(PNode *);
unsigned char * kmers(PTree * t, PKey current_key);
void getkeys_tree(PTree * t);
