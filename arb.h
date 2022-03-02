#ifndef _ARB_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#define CHAR_SIZE 128


typedef struct carte{
    char titlu[51], autor[41];
    int rating, nr_pagini;
}carte;

typedef struct Trie
{
    carte* isLeaf;             
    struct Trie* character[CHAR_SIZE];
    int nr_carti;
}Trie;

typedef struct Trie2
{
    Trie* isLeaf;             
    struct Trie2* character[CHAR_SIZE];
}Trie2;

struct Trie* getNewTrieNode();
struct Trie2* getNewTrieNode2();
void insert(struct Trie *head, char* str, carte* c);
void insert2(struct Trie2 *head, char* str, Trie *c);
carte* search(struct Trie* head, char* str);
Trie* search2(struct Trie2* head, char* str);
int hasChildren(struct Trie* curr);
int hasChildren2(struct Trie2* curr);
void display(Trie* root, char str[], int level, FILE *g);
void display_3_authors(Trie2* root, char str[], int level, FILE *g, int *nr, char prefix[]);
void display_3_books(Trie* root, char str[], int level, FILE *g, int *nr, char prefix[]);
int deletion(struct Trie **curr, char* str);
int deletion2(struct Trie2 **curr, char* str);
#endif