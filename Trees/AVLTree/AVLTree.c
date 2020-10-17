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
  for L0 we can use either of L1 and L-1 same logic applies to R1, R-1 and R0 
*/



