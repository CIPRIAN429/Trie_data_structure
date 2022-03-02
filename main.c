#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arb.h"

int main(int argc, char **argv) {

FILE *f = fopen(argv[1], "r");
FILE *g = fopen(argv[2], "w");

struct Trie* T1 = getNewTrieNode();

if(!T1)
    fprintf(g, "\nEROARE ALOCARE!!!\n");

struct Trie2* T2 = getNewTrieNode2();

if(!T2)
    fprintf(g, "\nEROARE ALOCARE!!!\n");

char * line = NULL;
size_t len = 0;

while (getline(&line, &len, f) != -1)
{
    char * comanda = strtok(line, " ");

    if(strcmp(comanda, "add_book") == 0)
    {
        carte * Carte = malloc(sizeof(carte));

        if(!Carte)
            fprintf(g, "\nEROARE ALOCARE!!!\n");

        char * Titlu = strtok(NULL, ":");
        strcpy(Carte->titlu, Titlu);
        char * Autor = strtok(NULL, ":");
        strcpy(Carte->autor, Autor);
        char * Rating = strtok(NULL, ":");
        Carte->rating = atoi(Rating);
        char * Nr_pagini = strtok(NULL, ":");
        Carte->nr_pagini = atoi(Nr_pagini);

        if (Nr_pagini[strlen(Nr_pagini) - 1] == '\n')
			Nr_pagini[strlen(Nr_pagini) - 1] = '\0';

		if (Nr_pagini[strlen(Nr_pagini) - 1] == '\r')
			Nr_pagini[strlen(Nr_pagini) - 1] = '\0';

        insert(T1, Carte->titlu, Carte);
        Trie * T3 = search2(T2, Carte->autor);
        
        if(T3 == NULL)
        {
            T3 = malloc(sizeof(Trie));

            if(!T3)
                fprintf(g, "\nEROARE ALOCARE!!!\n");

            insert(T3, Carte->titlu, Carte);
            insert2(T2, Carte->autor, T3);
            T3->nr_carti++;
        
        }
        else
        {   
            carte *aux = search(T3, Carte->titlu);

            //aceeasi carte nu va fi inserata de 2 ori
            if(aux)
            {
                if(strcmp(aux->titlu, Carte->titlu) !=0)
                {
                    insert(T3, Carte->titlu, Carte);
                    T3->nr_carti++;
                    insert2(T2, Carte->autor, T3);
                }
            }
            else
            {
                insert(T3, Carte->titlu, Carte);
                T3->nr_carti++;
                insert2(T2, Carte->autor, T3);
            }
        }

    }

    if(strcmp(comanda, "search_book") == 0)
    {   
        // caracterul * nu se regaseste in alfabet
        char * nume = strtok(NULL, "*"); 
        
        if (nume[strlen(nume) - 1] == '\n')
			nume[strlen(nume) - 1] = '\0';

		if (nume[strlen(nume) - 1] == '\r')
			nume[strlen(nume) - 1] = '\0';
        
        if (nume[strlen(nume) - 1] == '~')
        {
            nume[strlen(nume) - 1] = '\0';
            int val = 3;
            char c[100], prefix[100];
            strcpy(prefix, nume);
            display_3_books(T1, c, 0, g, &val, prefix);

            if(val == 3)
                fprintf(g, "Nicio carte gasita.\n");
        }
        else
        {
            carte * c;
            c = search(T1, nume);

            if(c->titlu != NULL)

                if(strcmp(c->titlu, nume) == 0)
                    fprintf(g, "Informatii recomandare: %s, %s, %d, %d\n", c->titlu, c->autor, c->rating, c->nr_pagini);
                else
                    fprintf(g, "Cartea %s nu exista in recomandarile tale.\n", nume);

            else fprintf(g, "Cartea %s nu exista in recomandarile tale.\n", nume);
        }
    }

    if(strcmp(comanda, "list_author") == 0)
    {
        char * autor = strtok(NULL, "*");

        if (autor[strlen(autor) - 1] == '\n')
			autor[strlen(autor) - 1] = '\0';

		if (autor[strlen(autor) - 1] == '\r')
			autor[strlen(autor) - 1] = '\0';

        if (autor[strlen(autor) - 1] == '~')
        {
			autor[strlen(autor) - 1] = '\0';
            int val = 3;
            char c[100], prefix[100];
            strcpy(prefix, autor);
            display_3_authors(T2, c, 0, g, &val, prefix);

            if(val == 3)
                fprintf(g, "Niciun autor gasit.\n");
        }
        else
        {
            Trie* a = search2(T2, autor);
            char c[100];

            if(!a)
                fprintf(g, "Autorul %s nu face parte din recomandarile tale.\n", autor);
            else
                display(a, c, 0, g);
        }
    }

    if(strcmp(comanda, "search_by_author") == 0)
    {
        char * autor = strtok(NULL, ":");

        if (autor[strlen(autor) - 1] == '\n')
			autor[strlen(autor) - 1] = '\0';

		if (autor[strlen(autor) - 1] == '\r')
			autor[strlen(autor) - 1] = '\0';
        
        if (autor[strlen(autor) - 1] == '~')
        {
			autor[strlen(autor) - 1] = '\0';
           
            int val = 3;
            char c[100], prefix[100];
            strcpy(prefix, autor);
            display_3_authors(T2, c, 0, g, &val, prefix);

            if(val == 3)
                fprintf(g, "Niciun autor gasit.\n");
        }
        else
        {    
            
            char * nume = strtok(NULL, "*");
          
            if (nume[strlen(nume) - 1] == '\n')
			    nume[strlen(nume) - 1] = '\0';

		    if (nume[strlen(nume) - 1] == '\r')
			    nume[strlen(nume) - 1] = '\0';
            
            Trie* a = search2(T2, autor);
              
            if (nume[strlen(nume) - 1] == '~')
            {
               
                if(!a)
                    fprintf(g, "Autorul %s nu face parte din recomandarile tale.\n", autor);
                else
                {  
                    nume[strlen(nume) - 1] = '\0';
                    int val = 3;
                    char c[100], prefix[100];
                    strcpy(prefix, nume);
                    display_3_books(a, c, 0, g, &val, prefix);

                    if(val == 3)
                        fprintf(g, "Nicio carte gasita.\n");
                }
            }
            else
            {    
                if(!a)
                    fprintf(g, "Autorul %s nu face parte din recomandarile tale.\n", autor);
                else
                    {
                        carte * c;
                        c = search(a, nume);

                        if(c->titlu != NULL)

                            if(strcmp(c->titlu, nume) == 0)
                                fprintf(g, "Informatii recomandare: %s, %s, %d, %d\n", c->titlu, c->autor, c->rating, c->nr_pagini);
                            else
                                fprintf(g, "Cartea %s nu exista in recomandarile tale.\n", nume);

                        else fprintf(g, "Cartea %s nu exista in recomandarile tale.\n", nume);

                    }
            }
        }
    }
    if(strcmp(comanda, "delete_book") == 0)
    {
        char * nume = strtok(NULL, "*");

        if (nume[strlen(nume) - 1] == '\n')
			nume[strlen(nume) - 1] = '\0';

		if (nume[strlen(nume) - 1] == '\r')
			nume[strlen(nume) - 1] = '\0';

        carte *c = search(T1, nume);

        if(c)
        {  
            Trie * a = search2(T2, c->autor);
            deletion(&T1, nume);
            deletion(&a, nume);
            a->nr_carti--;

            if(a->nr_carti == 0)
                deletion2(&T2, c->autor);
            
        }
        else
            fprintf(g, "Cartea %s nu exista in recomandarile tale.\n", nume);

    }

}

fclose(f);
fclose(g);

return 0;
}