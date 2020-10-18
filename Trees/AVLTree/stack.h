#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
struct Node {
 char data;
 struct Node *next;
 }*top=NULL;

void push(int x) {
  struct Node *t;
  t=(struct Node*)malloc(sizeof(struct Node));
  if(t==NULL)
    printf("stack is full\n");
  else {
    t->data=x;
    t->next=top;
    top=t;
  }
}
int pop() {
  struct Node *t;
  int x=-1;
  if(top==NULL)
    printf("Stack is Empty\n");
  else {
    t=top;
    top=top->next;
    x=t->data;
    free(t);
  }
  return x;
}
