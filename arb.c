#include "arb.h"

char ALPHABET[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";

struct Trie* getNewTrieNode()
{
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));

    if(!node)
        return NULL;

    node->isLeaf = malloc(sizeof(carte));
    int i;

    for (i = 0; i < CHAR_SIZE; i++) 
        node->character[i] = NULL;
 
    return node;
}

struct Trie2* getNewTrieNode2()
{
    struct Trie2* node = (struct Trie2*)malloc(sizeof(struct Trie2));

    if(!node)
        return NULL;

    node->isLeaf = malloc(sizeof(Trie));
    node->isLeaf = NULL;
    int i;
    
    for(i = 0; i < CHAR_SIZE; i++)
        node->character[i] = NULL;
 
    return node;
} 

void insert(struct Trie *head, char* str, carte *c)
{
    
    struct Trie* node = head;

    while(*str)
    {
        
        if(node->character[*str - 0] == NULL)
            node->character[*str - 0] = getNewTrieNode();

        node = node->character[*str - 0];
        str++;
        
    }
 
    node->isLeaf = c;
}

void insert2(struct Trie2 *head, char* str, Trie *c)
{
   
    struct Trie2* node = head;
    while(*str)
    {
       
        if(node->character[*str - 0] == NULL)
            node->character[*str - 0] = getNewTrieNode2();
        
        node = node->character[*str - 0];
        str++;
    }
 
    node->isLeaf = c;
}
 
carte* search(struct Trie* head, char* str)
{
    if(head == NULL)
        return 0;
    
    struct Trie* node = head;

    while (*str)
    {
        node = node->character[*str - 0];

        if(node == NULL) 
            return 0;

        str++;
    }
    
    return node->isLeaf;
}

Trie* search2(struct Trie2* head, char* str)
{
    if(head == NULL) 
        return 0;

    struct Trie2* node = head;

    while(*str)
    {
        node = node->character[*str - 0];
 
        if(node == NULL)
            return 0;
        
        str++;
    }

    return node->isLeaf;
}

void display(Trie* root, char str[], int level, FILE *g)
{
    if(root->isLeaf != NULL) 
    {   
        str[level] = '\0';
        // se afiseaza doar daca string-ul este complet format
        if(strcmp(root->isLeaf->titlu, str) == 0 && str[0] != '\0')
            fprintf(g, "%s\n",root->isLeaf->titlu);
        
    }

    int i = 0;

    while(ALPHABET[i] != '\0')
    { 
        if(root->character[ALPHABET[i] - 0]) 
        {
            str[level] = ALPHABET[i] - 0;
            display(root->character[ALPHABET[i] - 0], str, level + 1, g);      
        }

        i++; 
    }
}

void display_3_authors(Trie2* root, char str[], int level, FILE *g, int *nr, char prefix[])
{
    
    if(root->isLeaf != NULL) 
    {   
       
        str[level] = '\0';
        int ok = 1, i = 0;

        while(i < strlen(prefix))
        {
            if(str[i] != prefix[i])
            {
                ok = 0;
                break;
            }
            i++;
        }
        
        if(*nr > 0 && ok)   
        {
            fprintf(g, "%s\n", str);
            (*nr)--;
        }

    }

    int i = 0;

    while(ALPHABET[i] != '\0')
    { 
        if(root->character[ALPHABET[i] - 0]) 
        {
            str[level] = ALPHABET[i] - 0;
            display_3_authors(root->character[ALPHABET[i] - 0], str, level + 1, g, nr, prefix);      
        }

        i++; 
    }
    
}

void display_3_books(Trie* root, char str[], int level, FILE *g, int *nr, char prefix[])
{

    if(root->isLeaf != NULL) 
    {   
        
        str[level] = '\0';
        int ok = 1, i = 0;

        while(i < strlen(prefix))
        {
            if(str[i] != prefix[i])
            {
                ok = 0;
                break;
            }

            i++;
        }

        if(strcmp(root->isLeaf->titlu, str) == 0 && str[0] != '\0' && *nr > 0 && ok)    
        {
            fprintf(g, "%s\n", str);
            (*nr)--;
        }   
         
    }

    int i =0;

    while(ALPHABET[i] != '\0')
    { 
        if(root->character[ALPHABET[i] - 0]) 
        {
            str[level] = ALPHABET[i] - 0;
            display_3_books(root->character[ALPHABET[i] - 0], str, level + 1, g, nr, prefix);      
        }

        i++; 
    }
    
}

int hasChildren(struct Trie* node)
{
    int i;
    
    for(i = 0; i < CHAR_SIZE; i++)
    {
        if(node->character[i]) 
            return 1;      
        
    }
 
    return 0;
}

int hasChildren2(struct Trie2* node)
{
    int i;

    for(i = 0; i < CHAR_SIZE; i++)
    {
        if(node->character[i]) 
            return 1;    
        
    }
 
    return 0;
}
 
int deletion(struct Trie **node, char* str)
{
    
    if(*node == NULL) 
        return 0;
 
    if(*str)
    {  
        if(*node != NULL && (*node)->character[*str  - 0] != NULL &&
            deletion(&((*node)->character[*str - 0]), str + 1) &&
            (*node)->isLeaf == 0)
        {
            if(!hasChildren(*node))
            {
                free(*node);
                (*node) = NULL;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
 
    if(*str == '\0' && (*node)->isLeaf)
    {
        if(!hasChildren(*node))
        {
            free(*node);    
            (*node) = NULL;
            return 1;     
        }
 
        else
        {
            (*node)->isLeaf = NULL;
            return 0;     
        }
    }
 
    return 0;
}

int deletion2(struct Trie2 **node, char* str)
{
    if(*node == NULL) 
        return 0;
    
    if(*str)
    {
        if(*node != NULL && (*node)->character[*str - 0] != NULL &&
            deletion2(&((*node)->character[*str - 0]), str + 1) &&
            (*node)->isLeaf == 0)
        {
            if(!hasChildren2(*node))
            {
                free(*node);
                (*node) = NULL;
                return 1;
            }
            else 
                return 0;
            
        }
    }
 
    if(*str == '\0' && (*node)->isLeaf)
    {
        if(!hasChildren2(*node))
        { 
            free(*node);    
            (*node) = NULL;
            return 1;       
        }
        else
        {
            (*node)->isLeaf = NULL;
            return 0;      
        }
    }
 
    return 0;
}

