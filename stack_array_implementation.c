/*
    Autor: Adrian Kowalski
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item
{
    char * c_name;
    int n_age;
}  *Stack[100];

int n_top = 0;

int IsEmpty();
void Push(char * _n, int _a);
void Pop();
void ShowStack();

int main(void)
{
    printf("Stack\n");
    printf("-->2x push\n");
    Push("Chester Bennington", 38);
    Push("Rob Bourdon", 35);
    ShowStack();
    printf("-->1x pop\n");
    Pop();
    ShowStack();
    printf("-->1x push\n");
    Push("Brad Delson", 37);
    ShowStack();

    return 0;
}

int IsEmpty()
{
    if (n_top == 0)
        return 1;
    else
        return 0;
}

void Push(char * _n, int _a)
{
   struct Item * tmp;  
   tmp = (struct Item*)malloc(sizeof(struct Item));
   int n_counter = strlen(_n) + 1;    
   tmp->c_name = (char*)malloc(sizeof(char) * n_counter);
   strcpy(tmp->c_name, _n);
   tmp->n_age = _a;
   Stack[n_top] = tmp;
   ++n_top;
}

void Pop()
{
    if (IsEmpty() == 1)
        printf("Stos jest pusty\n");
    else
    {
        free(Stack[--n_top]->c_name);
        free(Stack[n_top]);
    }
}

void ShowStack()
{
    if (IsEmpty() == 1)
        printf("Stos jest pusty\n");
    else
    {
        int i = 0;
        for (i = 0; i < n_top; ++i)
            printf("%d: Imie: %s Wiek: %d\n",i+1, Stack[i]->c_name, Stack[i]->n_age); 
    }
}
