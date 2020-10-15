#include <stdio.h>
#include <stdlib.h>

struct Node {
 int data;
 struct Node *next;
 }*first=NULL, *second=NULL, *third=NULL;
 

void create(int A[],int n) {
  int i;
  struct Node *t,*last;
  first=(struct Node *)malloc(sizeof(struct Node));
  first->data=A[0]; 
  first->next=NULL;
  last=first;
  for(i=1;i<n;i++) {
    t=(struct Node*)malloc(sizeof(struct Node));
    t->data=A[i]; 
    t->next=NULL; 
    last->next=t;
    last=t;
  }
}

int count(struct Node *p)
{
  int l=0;
  while(p) {
    l++;
    p=p->next;
  }
  return l;
}

void display(struct Node *p)
{
  while(p!=NULL) {
    printf("%d ",p->data);
    p=p->next;
  }
}

void insert(struct Node *p,int index,int x)
{
  struct Node *t;
  int i;
  if(index < 0 || index > count(p))
    return;
  t=(struct Node *)malloc(sizeof(struct Node));
  t->data=x;
  if(index == 0) {
      t->next=first;
      first=t;
  } else {
    for(i=0;i<index-1;i++) p=p->next;
    t->next=p->next;
    p->next=t;
  }
}

void sortedInsert(struct Node *p,int x)
{
  struct Node *t,*q=NULL;
  t=(struct Node*)malloc(sizeof(struct Node));
  t->data=x;
  t->next=NULL;
  if(first==NULL)
    first=t;
  else {
    while(p && p->data<x)
    {
      q=p;
      p=p->next;
    }
    if(p==first) {
      t->next=first;
      first=t;
    } else {
      t->next=q->next;
    }
    q->next=t;
  }
}

int delete(struct Node *p,int index)
{
  struct Node *q=NULL;
  int x=-1,i;
  if(index < 1 || index > count(p))
    return -1;
  if(index==1) {
    q=first;
    x=first->data;
    first=first->next;
    free(q);
    return x;
  } else {
      for(i=0;i<index-1;i++) {
        q=p;
      }
      p=p->next;
      q->next=p->next;
      x=p->data;
      free(p);
      return x;
    }
 }

 void removeDuplicate(struct Node *p) {
  struct Node *q=p->next;
  while(q!=NULL)
  {
    if(p->data!=q->data) {
      p=q;
      q=q->next;
    }
    else {
      p->next=q->next;
      free(q);
      q=p->next;
    }
  }
}

void Merge(struct Node *p,struct Node *q)
{
  struct Node *last;
  if(p->data < q->data) {
    third=last=p;
    p=p->next;
    third->next=NULL;
  } else {
    third=last=q;
    q=q->next;
    third->next=NULL;
  }
  while(p && q)
  {
    if(p->data < q->data)
    {
      last->next=p;
      last=p;
      p=p->next;
      last->next=NULL;
    }
    else {
      last->next=q;
      last=q;
      q=q->next;
      last->next=NULL;
    }
  }
  if(p)
    last->next=p; 
  if(q)
    last->next=q;
}

void reverse(struct Node *p)
{
  struct Node *q=NULL,*r=NULL;
  while(p!=NULL) {
    r=q; 
    q=p;
    p=p->next; 
    q->next=r;
  }
  first=q;
}

void rReverse(struct Node *q,struct Node *p)
{
  if(p) {
   rReverse(p,p->next);
   p->next=q;
  } else first=q;
}

int isLoop(struct Node *f)
{
  struct Node *p,*q;
  p=q=f;
  do {
   p = p->next;
   q = q->next;
   q=q?q->next:q;
  } while(p && q && p!=q);
  if(p==q)
   return 1;
  else 
    return 0;
}

int main(int argc, const char * argv[]) {
  int A[]={10,20,30,40,50};
  create(A,5);
  insert(first,0,5);
  display(first);
  // struct Node *t1,*t2;
  // int A[]={10,20,30,40,50}; // Check if it's a loop 
  // create(A,5);
  // t1=first->next->next;
  // t2=first->next->next->next->next;
  // t2->next=t1;
  // printf("%d\n",isLoop(first));
 }