/*
    Autor: Adrian Kowalski
*/

#include <stdio.h>
#include <stdlib.h>

struct Item
{
    int n_age;
    struct Item * prev;
};

struct Item * top;

void Push(int _n);
void Pop();
int IsEmpty();
void ShowStack();

int main(void)
{   
    top = (struct Item*)malloc(sizeof(struct Item));
    top->n_age = 0;
    top->prev = NULL;

    printf("Stack\n");
    printf("-->2x push\n");
    Push(10);
    Push(20);
    ShowStack();
    printf("-->1x pop\n");
    Pop();
    ShowStack();
    printf("-->1x push\n");
    Push(30);
    ShowStack();

    return 0;
}

int IsEmpty()
{
    if (top->prev == NULL)
        return 1;
    else
        return 0;
}

void Push(int _n)
{
   struct Item * tmp;
   
   tmp = (struct Item*)malloc(sizeof(struct Item));
   tmp->n_age = _n;
   tmp->prev = top;
   top = tmp;
}

void Pop()
{
    if (IsEmpty() == 1)
        printf("Stos jest pusty\n");
    else
    {
        struct Item * tmp = top;
        top = top->prev;
        free(tmp);
    }
}

void ShowStack()
{
    int i = 0;
    struct Item * tmp = top;
    
    while(tmp->prev != NULL)
    {
        printf("%d: Wiek: %d\n", i+1, tmp->n_age);
        tmp = tmp->prev;
        ++i;
    }
}
