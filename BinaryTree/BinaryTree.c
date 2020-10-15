/*
  A 
B  C

Preorder ABC
Inorder BAC 
Postorder BCA 
Level order ABC 

Full, complete, strict binary trees 
K-D tree 
Randomized projection tree 

Full binary tree, all levels are full, it is always complete 
Complete binary tree, when traversed in level order, if elements are stored in array there are no blanks in the array
Strict binary tree, each node has either two or zero children 
For creating a binary tree a queue is used as well as a cursor pointer p and a temporary pointer t for node creation, here is the procedure: 
-We create a root node with left and right children pointers set to null 
-Enqueue its address. 
-Dequeue address from queue 
-point p to the dequeued address in this case the root, 
 -if p has a left child, 
 -Create node t with the left child's value 
 -Enqueue t's address 
 -Point p's left child to t 
 -if p does not have a left child 
 -If p has a right child
 -Create node t with the left child's value 
 -Enqueue t's address 
 -Dequeue the next address for the next element and point p to it 
 -If p does not have a right child 
 -Dequeue the next address 
 -Repeat until queue is empty 
 -We will use a value of -1 to signify a left or right child is empty 
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "Queue.h"
struct Node *root=NULL;

void Treecreate() {
  struct Node *p,*t;
  int x;
  struct Queue q;
  create(&q,100);
  printf("Eneter root value ");
  scanf("%d",&x);
  root=(struct Node *)malloc(sizeof(struct Node));
  root->data=x;
  root->lchild=root->rchild=NULL;
  enqueue(&q,root);
  while(!isEmpty(q)) {
    p=dequeue(&q);
    printf("eneter left child of %d ",p->data);
    scanf("%d",&x);
    if(x!=-1) {
      t=(struct Node *)malloc(sizeof(struct Node));
      t->data=x;
      t->lchild=t->rchild=NULL;
      p->lchild=t;
      enqueue(&q,t);
    }
    printf("eneter right child of %d ",p->data);
    scanf("%d",&x);
    if(x!=-1) {
      t=(struct Node *)malloc(sizeof(struct Node));
      t->data=x;
      t->lchild=t->rchild=NULL;
      p->rchild=t;
      enqueue(&q,t);
    }
  }
}

void Preorder(struct Node *p) {
  if(p) {
    printf("%d ",p->data);
    Preorder(p->lchild); 
    Preorder(p->rchild);
  }
}
void Inorder(struct Node *p) {
  if(p) {
    Inorder(p->lchild);
    printf("%d ",p->data);
    Inorder(p->rchild);
  }
}
void Postorder(struct Node *p) {
  if(p) {
    Postorder(p->lchild); 
    Postorder(p->rchild);
    printf("%d ",p->data);
  }
}

int main() {
  Treecreate();
  Preorder(root);
  printf("\nPost Order ");
  Postorder(root);
  return 0;
}

 