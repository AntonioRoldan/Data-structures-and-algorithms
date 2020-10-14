#include <stdio.h>
#include <stdlib.h>

struct Node {
 int data;
 struct Node *next;
 }*Head;

void create(int A[],int n) {
  struct Node *next;
 
  int i;
  struct Node *t,*last;
  Head=(struct Node*)malloc(sizeof(struct Node));
  Head->data=A[0]; Head->next=Head;
  last=Head;
  for(i=1;i<n;i++) {
    t=(struct Node*)malloc(sizeof(struct Node));
    t->data=A[i];
    t->next=last->next;
    last->next=t;
    last=t;
  }
}

void display(struct Node *h)
{
  do {
    printf("%d ",h->data);
    h=h->next;
  } while(h!=Head);
  printf("\n");
}

void rDisplay(struct Node *h)
{
  static int flag=0;
  if(h!=Head || flag==0) {
    flag=1;
    printf("%d ",h->data);
    rDisplay(h->next);
  }
  flag=0;
}

int length(struct Node *p) {
  int len=0;
  do {
    len++;
    p=p->next;
  } while(p!=Head);
  return len;
}

void insert(struct Node *p,int index, int x)
{
  struct Node *t;
  int i;
  if(index < 0 || index > length(p)) return;
    if(index==0) {
      t=(struct Node *)malloc(sizeof(struct Node));
      t->data=x;
      if(Head==NULL) {
          Head=t;
          Head->next=Head;
      } else {
        while(p->next!=Head)p=p->next;
        p->next=t;
        t->next=Head;
        Head=t;
      }
    } else {
      for(i=0;i<index-1;i++)p=p->next;
      t=(struct Node *)malloc(sizeof(struct Node));
      t->data=x;
      t->next=p->next;
      p->next=t;
    }
}
int delete(struct Node *p,int index)
{
  struct Node *q;
  int i,x;
  if(index <0 || index > length(Head)) return -1;
  if(index == 1) {
    while(p->next!=Head)p=p->next;
    x=Head->data;
    if(Head==p) {
      free(Head);
      Head=NULL;
    } else {
        p->next=Head->next;
        free(Head);
        Head=p->next;
      }
  } else {
    for(i = 0; i < index-2; i++)
    p=p->next;
    q=p->next;
    p->next=q->next;
    x=q->data;
    free(q);
  }
  return x;
}

int main(int argc, const char * argv[]) {
  int A[]={10,20,30,40,50};
  create(A,5);
  insert(Head, 0, 5);
  display(Head);
 }
