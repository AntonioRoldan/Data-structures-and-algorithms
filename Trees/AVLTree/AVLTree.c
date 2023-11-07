
/*
  What happens with the children of the node that we will replace the root by?
  They maintain their position, right or left, while being added to the left and right
  children of the root.
  We only count the first three nodes when performing a rotation
  so the root will be replaced by the third node on the left, if it is LL or LR imbalance,
  or the right if it is RR or RL imbalance.
  This applies to both single rotation and double rotation.
  Single rotation is used for Left of left rotation and right of right rotation
  Double rotation for left of right and right of left
  So we calculate the height of the tree on the right and the left side
  of the root, this is the balance factor.
  Balanced values are -1, 0 and 1.
  So the absolute value of the balance factor must be <= 1
  for the tree to be balanced.
  If imbalanced it will only have the value of two or minus 2
  Since balancing rotations are always performed upon insertion and deletion
  If it is a LL imbalance the third node on the left takes the position of the left child of the root,
  while the left child takes the position of the root and the root becomes the right child of our new root
  If the replacing node has children on the right side, we respect the positioning and add them as left children of the right
  child of the new root.
  RR imbalance is the same but in right-left direction.
  If it is a LR imbalance, we take the left children of the replacing node and keep them on the left side
  of the root node, they will be the right children of the left child of the new node
  which is the same as the left child of the old root.
  Its right children are added as the left children of the right child of our new root which is the old root
  For deletion we have L1 L-1 and L0 rotations depending on the balance factor
  of the left child of the root with L1 being LL rotation, L-1 being LR rotation.
  These cases apply when deleting a node from the right side of the root
  for L0 we can use either of L1 and L-1 same logic applies to R1, R-1 and R0

  SIMPLE EXPLANATION 
  The above text is overtly complex this is simple. 
  Once an element is added to the tree in a BST like fashion and as we have pushed visited nodes into a stack 
  We pop the nodes from the stack going in the opposite direction we went when we added the element 
  and find the balance factor which cannot be any value other than one, zero and minus one. 
  So, the tree is imbalanced as soon as our balance factor, which is the result of subtracting the height of 
  the left sub-tree from the right sub-tree or viceversa (hence why we can have negative values), hits 2 or minus 2.
  We perform rotations depending on the imbalance to correct it.  
  
  
  The following diagram will help understand LR rotation
        p                   plr
      /   \   ------>    /      \
     pl                pl        p
        \                \     /
         plr
        /   \
  
  pl = p->lChild;
  plr = pl->rChild;
  pl->rChild = plr->lChild;
  p->lChild = plr->rChild;

  plr->lChild = pl;
  plr->rChild = p;

 
  Now an example of LL rotation 
        p              pl
     /    \    ->    /    \
    pl                     p
   /  \                   /
      plr               plr
  
  pl = p->lChild;
  plr = pl->rChild;

  pl->rChild = p;
  p->lChild = plr;

 
  In this case we use the pointer plr to keep track of the soon-to-be root's right child
  Whenever we find an imbalance at any node in the tree
  we always perform the rotation from the third node starting from above
  If we have a balance factor of -2 since the balance factor is the result
  of lh - rh we have a right imbalance
  If the right child of the root whose subtree/tree is imbalanced is -1
  we have an RR imbalance because the third child is on the right since bf = lh - rh
  if it is 1 we have RL because the third child is on the left
  Same with left imbalances.
  Here is how to understand recursive deletion

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

int height(struct Node *p) {
  int x=0,y=0;
  if(!p)return 0;
  x=height(p->lchild);
  y=height(p->rchild);
  return x>y?x+1:y+1;
}

int iHeight(struct Node *p) {
  int hl;
  int hr;
 
  hl = (p && p->lchild) ? p->lchild->height : 0;
  hr = (p && p->rchild) ? p->rchild->height : 0;
 
  return hl > hr ? hl + 1 : hr + 1;
}

void Insert(int key) {
  struct Node *t=root;
  struct Node *r=NULL,*p;
  if(root==NULL) {
    p=(struct Node *)malloc(sizeof(struct Node));
    p->data=key;
    p->bf=0;
    p->lchild=p->rchild=NULL;
    root=p;
    return;
  }

  while(t!=NULL) {
    r=t;
    if(key<t->data)
      t=t->lchild;
    else if(key>t->data)
      t=t->rchild;
    else
    return;
  }
  p=(struct Node *)malloc(sizeof(struct Node));
  p->data=key;
  p->lchild=p->rchild=NULL;
  if(key<r->data) r->lchild=p;
  else r->rchild=p;
}

int balanceFactor(struct Node *p) {
  int hl;
  int hr;
 
  hl = (p && p->lchild) ? p->lchild->height : 0;
  hr = (p && p->rchild) ? p->rchild->height : 0;
 
  return hl - hr;
}

struct Node * iLLRotation(struct Node *p) {
  struct Node *pl=p->lchild;
  p->lchild=pl->rchild;
  pl->rchild=p;
  
  p->height = iHeight(p);
  pl->height = iHeight(pl);
  return pl;
}

struct Node * iLRRotation(struct Node* p){
    struct Node *pl = p->lchild;
    struct Node *plr = pl->rchild;
    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;
    plr->rchild = p;
    plr->lchild = pl;
    pl->height = iHeight(pl);
    p->height = iHeight(p);
    plr->height = iHeight(plr);
    if(p == root){
        root = plr;
    }
    return plr;
}

struct Node * iRLRotation(struct Node *p) {
    struct Node *pr = p->rchild;
    struct Node *prl = pr->lchild;
    pr->lchild = prl->rchild;
    p->rchild = prl->lchild;
    prl->lchild = p;
    prl->rchild = pr;
    pr->height = iHeight(pr);
    p->height = iHeight(p);
    prl->height = iHeight(prl);
    if(p == root){
        root = prl;
    }
    return prl;
}

struct Node * iRRRotation(struct Node* p){
    struct Node *pr = p->rchild;
    p->rchild = pr->lchild;
    pr->lchild = p;
    p->height = iHeight(p);
    pr->height = iHeight(p);
    if(p == root){
        root = pr;
    }
    return pr;
}
struct Node * LLRotation(struct Node *p) {
  int lbf,rbf;
  struct Node *pl=p->lchild;
  pl->bf=0;
  p->lchild=pl->rchild;
  pl->rchild=p;
  lbf=height(p->lchild)+1; rbf=height(p->rchild)+1;
  p->bf=lbf-rbf;
  if(p==root)root=pl;
  return pl;
}
struct Node *LRRotation(struct Node *p) {
  int lbf,rbf;
  struct Node *pl=p->lchild;
  struct Node *plr=pl->rchild;
  plr->bf=0;
  p->lchild=plr->rchild;
  pl->rchild=plr->lchild;

  plr->lchild=pl;
  plr->rchild=p;
  lbf=height(p->lchild)+1; rbf=height(p->rchild)+1;
  p->bf=lbf-rbf;
  lbf=height(pl->lchild)+1; rbf=height(pl->rchild)+1;
  pl->bf=lbf-rbf;
  if(p==root)root=plr;
  return plr;
}
struct Node *RRRotation(struct Node *p)
{
  int lbf,rbf;
 struct Node *pr=p->rchild;
 pr->bf=0;
 p->rchild=pr->lchild;
 pr->lchild=p;
 lbf=height(p->lchild)+1; rbf=height(p->rchild)+1;
 p->bf=lbf-rbf;
 if(p==root)root=pr;
 return pr;
}
struct Node *RLRotation(struct Node *p)
{
  int lbf,rbf;
 struct Node *pr=p->rchild;
 struct Node *prl=pr->lchild;
 prl->bf=0;
  p->rchild=prl->lchild;
 pr->lchild=prl->rchild;
 prl->rchild=pr;
 prl->lchild=p;
 lbf=height(p->lchild)+1; rbf=height(p->rchild)+1;
 p->bf=lbf-rbf;
 
  lbf=height(pr->lchild)+1; rbf=height(pr->rchild)+1;
 pr->bf=lbf-rbf;
 if(p==root)root=prl;
 return prl;
}


struct Node* RInsert(struct Node *p,int key)
{
  struct Node *t;
  int lbf,rbf;
  if(p==NULL) {
    t=(struct Node *)malloc(sizeof(struct Node));
    t->data=key;
    t->bf=0;
    t->lchild=t->rchild=NULL;
    return t;
  }
  if(key<p->data)
    p->lchild=RInsert(p->lchild,key);
  else if(key>p->data)
    p->rchild=RInsert(p->rchild,key);
  lbf=height(p->lchild)+1;
  rbf=height(p->rchild)+1;
  p->bf=lbf-rbf;
  if(p->bf==2 && p->lchild->bf==1)
    return LLRotation(p);
  if(p->bf==2 && p->lchild->bf==-1)
    return LRRotation(p);
  if(p->bf==-2 && p->rchild->bf==-1)
    return RRRotation(p);
  if(p->bf==-2 && p->rchild->bf==1)
    return RLRotation(p);
  return p;
}

void iInsert(struct Node* p, int key){
    struct Node *q = (struct Node *)malloc(sizeof(struct Node));
    struct Node *t;
    int lh, rh;
    if(p==NULL) {
      t=(struct Node *)malloc(sizeof(struct Node));
      t->data=key;
      t->bf=0;
      t->height = 1;
      t->lchild=t->rchild=NULL;
      t->isRoot = true;
      p = t;
      root = t;
      return;
    }
    while(p != NULL){
        push(p); // We push each visited node in a stack so we can do balancing rotations iteratively
        q = p; //After inserting node
        if(key < p->data){
            p = p->lchild;
        } else if(key > p->data){
            p = p->rchild;
        } else {
            return;
        }
    }
    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = key;
    t->rchild = t->lchild = NULL;
    t->height = 1;
    t->isRoot = false;
    t->bf = 0;
    if(key > q->data){
        q->rchild = t;
    } else if(key < q->data) {
        q->lchild = t;
        
    }
    if(q->isRoot){
        return;
    }
    while(top != NULL){ // While stack is not empty
        p = pop();
        rh = p->rchild ? p->rchild->height : 0;
        lh = p->lchild ? p->lchild->height : 0;
        p->bf = rh - lh;
        if(p->bf == 2 && p->lchild->bf == 1){
            p = iLLRotation(p);
        } else if(p->bf == 2 && p->lchild->bf == -1){
            p = iLRRotation(p);
        } else if(p->bf == -2 && p->rchild->bf == -1){
            p = iRRRotation(p);
        } else if(p->bf == -2 && p->rchild->bf == 1){
            p = iRLRotation(p);
        }
    }
}

void Inorder(struct Node *p){
  if(p){
    Inorder(p->lchild);
    printf("->\n");
    printf("%d",p->data);
    Inorder(p->rchild);
  }
}
struct Node * Search(int key){
  struct Node *t=root;
  while(t!=NULL){
    if(key==t->data)
      return t;
    else if(key<t->data)
      t=t->lchild;
    else
      t=t->rchild;
  }
  return NULL;
}

struct Node *InSucc(struct Node *p) {
  while(p && p->lchild!=NULL)
    p=p->lchild;
  return p;
}

struct Node *InPre(struct Node *p) {
  while(p && p->rchild!=NULL)
    p=p->rchild;
  return p;
}

struct Node* Delete(struct Node *p, int key) {
  struct Node *q;

  if(p == NULL)
    return NULL;
  if(p->lchild == NULL && p->rchild == NULL){
    if(p==root)
      root=NULL;
    free(p);
    return NULL;
  }
  if(key < p->data)
    p->lchild = Delete(p->lchild, key);
  else if(key > p->data)
    p->rchild = Delete(p->rchild, key);
  else {
    if((p->lchild && p->lchild->height) > (p->rchild && p->rchild->height)) {
      q = InPre(p->lchild);
      p->data = q->data;
      p->lchild = Delete(p->lchild, p->data);
    } else {
      q = InSucc(p->rchild);
      p->data = q->data;
      p->rchild = Delete(p->rchild, p->data);
    }
  }
  p->height = height(p);

  if(p->bf == 2) {
    if(p->lchild->bf == 1)
      return LLRotation(p);
    else
      return LRRotation(p);
  }
  if(p->bf == -2) {
    if(p->rchild->bf == -1)
      return RRRotation(p);
    else
      return RLRotation(p);
  }
  return p;
}

int main() {
  // Note you cannot combine iterative insert and recursive insert
  iInsert(root,50);
  iInsert(root,40);
  iInsert(root,20);
  iInsert(root,10);
  iInsert(root,42);
  iInsert(root,46);
  Inorder(root);
  printf("\n");
  return 0;
}



