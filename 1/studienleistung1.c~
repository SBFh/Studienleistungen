#include <stdio.h>
#include <stdlib.h>

typedef struct _link
{ 
  int data;
  struct _link *next;
} link;

link *first = NULL;
link *last = NULL;

void Add(link *item)
{
  if (item == NULL)
  {
   return; 
  }
  if (first == NULL)
  {
   first = item;
   last = item;
   return;
  }
  last->next = item;
  last = item;
}

void Delete(link *item)
{
  if (first == NULL || item == NULL)
  {
   return; 
  }
  if (first == item && last == item)
  {
    item->next = NULL;
    first = NULL;
    last = NULL;
    return;
  }
  if (first == item)
  {
    first = first->next;
    item->next = NULL;
    return;
  }
  link *current = first;
  while (current != NULL)
  {
   if (current->next == item)
   {
    if (item == last)
    {
     last = current; 
     current->next = NULL;
    }
    else
    {
     current->next = item->next;
    }
    item->next = NULL;
    return;
   }
   current = current->next;
  }
}

link *Create(int data)
{
  link* newItem = malloc(sizeof *newItem);
  newItem->data = data;
  newItem->next = NULL;
  return newItem;
}

void PrintList()
{
 link *current = first;
 while (current != NULL)
 {
   printf("%i\n", current->data);
   current = current->next;
 }
 printf("\n");
}

int main()
{
  link *item1, *item2, *item3;
  item1 = Create(1);
  item2 = Create(2);
  item3 = Create(3);
  
  Add(item1);
  Add(item2);
  Add(item3);
  
  PrintList();
  
  Delete(item2);
  
  PrintList();
  
  Add(item2);
  
  PrintList();
  
  Delete(item3);
  
  PrintList();
  
  Delete(item1);
  
  PrintList();
  
  Delete(item2);
  
  PrintList();
  
  Add(item3);
  
  PrintList();
  
  Add(item2);
  Add(item1);
  
  PrintList();
  
}