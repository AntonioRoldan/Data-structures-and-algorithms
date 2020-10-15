#include <iostream>

using namespace std;
 
class Node{
  public:
    Node* lchild;
    int data;
    Node* rchild;
};
 
class BST{
  private:
    Node* root;
  public:
    BST(){ root = nullptr; }
    Node* getRoot(){ return root; }
    void iInsert(int key);
    void Inorder(Node* p);
    Node* iSearch(int key);
    Node* rInsert(Node* p, int key);
    Node* rSearch(Node* p, int key);
    Node* rDelete(Node* p, int key);
    Node* iDelete(Node* p, int key);
    int Height(Node* p);
    Node* InPre(Node* p);
    Node* InSucc(Node* p);
};
 
void BST::iInsert(int key) {
 
    Node* t = root;
    Node* p;
    Node* r;
 
    // root is empty
  if (root == nullptr){
    p = new Node;
    p->data = key;
    p->lchild = nullptr;
    p->rchild = nullptr;
    root = p;
    return;
  }
 
  while(t != nullptr){
    r = t;
    if (key < t->data){
      t = t->lchild;
    } else if (key > t->data){
      t = t->rchild;
    } else {
      return;
    }
  }
 
    // Now t points at NULL and r points at insert location
  p = new Node;
  p->data = key;
  p->lchild = nullptr;
  p->rchild = nullptr;
 
  if (key < r->data){
    r->lchild = p;
  } else {
    r->rchild = p;
  }
 
}
 
void BST::Inorder(Node* p) {
  if (p){
    Inorder(p->lchild);
    cout << p->data << ", " << flush;
    Inorder(p->rchild);
  }
}
 
Node* BST::iSearch(int key) {
  Node* t = root;
  while (t != nullptr){
    if (key == t->data){
      return t;
    } else if (key < t->data){
        t = t->lchild;
    } else {
        t = t->rchild;
      }
    }
    return nullptr;
}
 
Node* BST::rInsert(Node *p, int key) {
  Node* t;
  if (p == nullptr){
    t = new Node;
    t->data = key;
    t->lchild = nullptr;
    t->rchild = nullptr;
    return t;
  }
 
  if (key < p->data){
    p->lchild = rInsert(p->lchild, key);
  } else if (key > p->data){
    p->rchild = rInsert(p->rchild, key);
  }
  return p;  // key == p->data?
}
 
Node* BST::rSearch(Node *p, int key) {
  if (p == nullptr){
    return nullptr;
  }
 
  if (key == p->data){
    return p;
  } else if (key < p->data){
    return rSearch(p->lchild, key);
  } else {
    return rSearch(p->rchild, key);
  }
}
 
Node* BST::rDelete(Node *p, int key) {
  Node* q;
 
  if (p == nullptr){
      return nullptr;
  }
 
  if (p->lchild == nullptr && p->rchild == nullptr){
    if (p == root){
      root = nullptr;
    }
    delete p;
    return nullptr;
  }
 
  if (key < p->data){
      p->lchild = Delete(p->lchild, key);
  } else if (key > p->data){
      p->rchild = Delete(p->rchild, key);
  } else {
    if (Height(p->lchild) > Height(p->rchild)){
        q = InPre(p->lchild);
        p->data = q->data;
        p->lchild = Delete(p->lchild, q->data);
    } else {
        q = InSucc(p->rchild);
        p->data = q->data;
        p->rchild = Delete(p->rchild, q->data);
    }
  }
  return p;
}

Node* BST::iDelete(Node* root, int key) 
{ 
  Node *curr = root; 
  Node *prev = NULL; 
  
  // Check if the key is actually 
  // present in the BST. 
  // the variable prev points to 
  // the parent of the key to be deleted. 
  while (curr != NULL && curr->data != key) { 
      prev = curr; 
      if (key < curr->data) 
        curr = curr->lchild; 
      else
        curr = curr->rchild; 
    } 
  
  if (curr == NULL) { 
    cout << "Key " << key 
    << " not found in the"
    << " provided BST.\n"; 
    return root; 
  } 
  
  // Check if the node to be 
  // deleted has atmost one child. 
  if (curr->lchild == NULL 
    || curr->rchild == NULL) { 
  
    // newCurr will replace 
    // the node to be deleted. 
    Node *newCurr; 
  
    // if the left child does not exist. 
    if (curr->lchild == NULL) 
      newCurr = curr->rchild; 
    else
      newCurr = curr->lchild; 
  
    // check if the node to 
    // be deleted is the root. 
    if (prev == NULL) 
      return newCurr; 
  
    // check if the node to be deleted 
    // is prev's left or right child 
    // and then replace this with newCurr 
    if (curr == prev->lchild) 
      prev->lchild = newCurr; 
    else
      prev->rchild = newCurr; 
  
    // free memory of the 
    // node to be deleted. 
    delete curr; 
  } 
  // node to be deleted has 
  // two children. 
  else { 
    Node* p = NULL; 
    Node* temp; 
  
        // Compute the inorder successor 
    temp = curr->rchild; 
    while (temp->lchild != NULL) { 
      p = temp; 
      temp = temp->lchild; 
    } 
  
    // check if the parent of the inorder 
    // successor is the root or not. 
    // if it isn't, then make the 
    // left child of its parent equal to the 
    // inorder successor's right child. 
    if (p != NULL) 
      p->lchild = temp->rchild; 
    // Since it is the inorder successor if it has children it will always be
    // One child and that is the right child, if it was in order predecessor it would be the left child 
    // And we would replace the parent's right child 
    // If the in order successor's right child, the only child it has, is null we set p->lchild to null
    
    
    // if the inorder successor was the 
    // root, then make the right child 
    // of the node to be deleted equal 
    // to the right child of the inorder 
    // successor. 
    else
      curr->rchild = temp->rchild; 
  
    curr->data = temp->data; 
    delete temp; 
  } 
  return root; 
} 
 
int BST::Height(Node *p) {
  int x;
  int y;
  if (p == nullptr){
      return 0;
  }
  x = Height(p->lchild);
  y = Height(p->rchild);
  return x > y ? x + 1 : y + 1;
}
 
Node* BST::InPre(Node *p) {
  while (p && p->rchild != nullptr){
      p = p->rchild;
  }
  return p;
}
 
Node* BST::InSucc(Node *p) {
  while (p && p->lchild != nullptr){
      p = p->lchild;
  }
  return p;
}
 
 
int main() {
 
  BST bst;
 
    // Iterative insert
  bst.iInsert(10);
  bst.iInsert(5);
  bst.iInsert(20);
  bst.iInsert(8);
  bst.iInsert(30);
 
    // Inorder traversal
  bst.Inorder(bst.getRoot());
  cout << endl;
 
    // Iterative search
  Node* temp = bst.iSearch(2);
  if (temp != nullptr){
    cout << temp->data << endl;
  } else {
    cout << "Element not found" << endl;
  }
 
    // Recursive search
  temp = bst.rSearch(bst.getRoot(), 20);
  if (temp != nullptr){
    cout << temp->data << endl;
  } else {
    cout << "Element not found" << endl;
  }
 
    // Recursive insert
  bst.rInsert(bst.getRoot(), 50);
  bst.rInsert(bst.getRoot(), 70);
  bst.rInsert(bst.getRoot(), 1);
  bst.Inorder(bst.getRoot());
  cout << "\n" << endl;
 
    // Inorder predecessor and inorder successor
  BST bs;
  bs.iInsert(5);
  bs.iInsert(2);
  bs.iInsert(8);
  bs.iInsert(7);
  bs.iInsert(9);
  bs.iInsert(1);
 
  temp = bs.InPre(bs.getRoot());
  cout << "InPre: " << temp->data << endl;
 
  temp = bs.InSucc(bs.getRoot());
  cout << "InSucc: " << temp->data << endl;
 
  bs.Inorder(bs.getRoot());
  cout << endl;
 
    // Delete
  bs.rDelete(bs.getRoot(), 7);
  bs.Inorder(bs.getRoot());
    
  return 0;
}