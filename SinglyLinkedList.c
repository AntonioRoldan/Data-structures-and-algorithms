#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  int length;
  struct Node *next;
};

struct Node newNode(int data)
{
  struct Node newNode = {.data = data,
                         .next = malloc(sizeof(newNode)),
                         .length = 1};
  return newNode;
};

void delPtrNextNode(struct Node *node)
{
  free(node->next);
};

void deleteAt(struct Node *startNode, int index)
{

}

void deleteByValue(struct Node *startNode, int data)
{

}
void print(struct Node *startNode)
{
  int currentIndex = startNode->length - 1;
  struct Node currentNode;
  currentNode = *startNode;
  printf("Value: %d\n", startNode->data);
  while (currentIndex)
  {
    currentNode = *currentNode.next;
    printf("Value: %d\n", currentNode.data);
    currentIndex--;
  };
};

void insert(struct Node *startNode, int data)
{
  struct Node node = newNode(data);
  if (startNode->length == 1)
  {
    *startNode->next = node;
  }
  else
  {
    struct Node currentNode = *startNode;
    int currentIndex = startNode->length - 1;
    while (currentIndex)
    {
      currentNode = *currentNode.next;
      currentIndex--;
    };
    *currentNode.next = node;
  }
  startNode->length++;
  printf("New node of value %d inserted\n", data);
};

int main()
{
  // int testInteger;
  // printf("Enter an integer: ");
  // scanf("%d",&testInteger);
  // printf("Number = %d\n",testInteger);
  // return 0;
  struct Node startNode = newNode(1);
  int data = 2;
  insert(&startNode, 2);
  insert(&startNode, 3);
  print(&startNode);
  return 0;
}
