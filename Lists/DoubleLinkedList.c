#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data; 
  struct Node *next; 
  struct Node *prev; 
} *first=NULL; 

void create(int A[], int n) {
  struct Node *t, *last; 
  int i; 

  first = (struct Node *)malloc(sizeof(struct Node));
  first->data = A[0];
  first->prev = first->next = NULL;
  last = first; 
  for (i=1; i<n; i++) {
    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = A[i];
    t->next = last->next; // It will always equal NULL 
    t->prev = last; 
    last->next = t;
    last = t; 
  }
}

void display(struct Node *p) {
  while (p){
    printf("%d", p->data);
    p = p->next;
  }
  printf("\n");
}

void insert(struct Node *p, int index, int x) {
  struct Node *t; 
  t = (struct Node *)malloc(sizeof(struct Node));
  t->data = x;
  if(index < 0 || index > length(p)) return; 
  if(index == 0){
    t->next = first;
    t->prev = NULL;
    first->prev = t;
    first = t; 
  }
  for(int i = 0; i < index - 1; i++){
    p = p->next;
  }
  if(p->next) p->next->prev = t;
  t->next = p->next;
  t->prev = p; 
  p->next = t; 
}

int delete(struct Node *p, int index) {
  int x; 
  if(index < 1 || index > length(p)) return; 
  if(index == 1) { 
    first = first->next; 
    if(first) first->prev = NULL; 
    x = p->data;
    free(p);
  } else {
     for(int i = 0; i <index - 1;i++) {
      p = p->next;
     }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    x = p->data; 
    free(p);
  }
  return x; 
}

int length(struct Node *p) {
  int len = 0; 
  while(p) {
    len++; 
    p = p->next;
  }
  return len;
}

int main(int argc, const char * argv[]){
  int A[]={10,20,30,40,50};
  create(A, 5);
  insert(first, 0, 5); 
  insert(first, 3, 70);
  display(first);
}