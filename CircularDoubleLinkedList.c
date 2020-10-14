#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
} *Head;

void create(int A[], int size)
{
  struct Node *t, *last;
  t = (struct Node *)malloc(sizeof(struct Node));
  t->data = A[0];
  Head = t;
  Head->prev = Head;
  Head->next = Head;
  last = Head;
  for(int i = 1; i < size; i++){
    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = A[i];
    t->prev = last;
    t->next = last->next; // last->next will always point to head
    last->next = t; // We want the last node to point to our newly created node rather than the head, which our newly created node already points to
    last = t;
    Head->prev = last;
  }
};

void display(struct Node *head)
{
  do {
    printf("%d ", head->data);
    head = head->next;
  } while(head != Head);
  printf("\n");
};

void insert(struct Node *p, int pos, int x)
{
  struct Node *t;
  t = (struct Node *)malloc(sizeof(struct Node));
  t->data = x;
  if(pos == 0) {
    if(Head == NULL){
        Head = t;
        Head->next = Head;
        Head->prev = Head;
    }
    else {
      t->next = Head;
      p = p->prev; // we move p to the last node
      p->next = t; // we point the next pointer of the last node to t
      Head->prev = t; // We point head's prev to our newly created node
      t->prev = p; // We point our newly created node's previous pointer to the last node
      Head = t; // And make it our new head
    }
  } else {
    for(int i = 0; i < pos - 1; i++) {
      p = p->next;
    }
    t->next = p->next;
    p->next = t;
    t->prev = p;
  }
};

int delete(struct Node *p, int pos)
{
  int x;
  if(pos == 1) {
    x = Head->data;
    while(p->next != Head) p = p->next;
    if(p == Head){
      free(Head);
      Head = NULL;
    } else {
      p->next = Head->next;
      Head->next->prev = p;
      free(Head);
      Head = p->next;
    }
  } else {
      for(int i = 0; i < pos - 1; i++) {
        p = p->next;
      }
      x = p->data;
      p->prev->next = p->next;
      p->next->prev = p->prev;
      free(p);
  }
  return x;
};

int main(int argc, const char * argv[])
{
  int A[] = {2, 6, 7};
  create(A, 3);
  display(Head);
  insert(Head, 2, 5);
  insert(Head, 4, 8);
  insert(Head, 0, 2);
  display(Head);
  delete(Head, 1);
  delete(Head, 4);
  display(Head);

  return 0;
}

