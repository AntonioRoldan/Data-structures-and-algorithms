//
//  stack.h
//  CircularDoubleLinkedList
//
//  Created by Antonio Miguel Roldan de la Rosa on 16/10/2020.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

struct Node {
  int *keys;
  struct Node* left;
  struct Node* middle;
  struct Node* right;
  bool isRoot;
} *root=NULL;

struct Stack
{
  int size;
  int top;
  struct Node **S;
};

void create(struct Stack *st) {
  printf("Enter Size");
  scanf("%d",&st->size);
  st->top=-1;
  st->S=(struct Node **)malloc(st->size*sizeof(struct Node*));
}

void push(struct Stack *st, struct Node * x) {
  if(st->top==st->size-1)
  printf("Stack overflow\n");
  else {
    st->top++;
    st->S[st->top]=x;
  }
 }

struct Node *pop(struct Stack *st) {
  struct Node *x=NULL;
  if(st->top==-1) return NULL;
  else {
    x=st->S[st->top--];
    return x;
  }
}

int isEmpty(struct Stack st) {
  if(st.top==-1)
    return 1;
  return 0;
}

int isFull(struct Stack st) {
  return st.top==st.size-1;
}

struct Node *stackTop(struct Stack st) {
  if(!isEmpty(st)) return st.S[st.top];
  return NULL;
}




#endif /* stack_h */
