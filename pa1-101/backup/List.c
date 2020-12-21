//-----------------------------------------------------------------------------
// Brandon Delgado, bdelgad3
// 2020 Spring CSE101 PA1
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj
{
   int data;
   struct NodeObj *next;
   struct NodeObj *prev;
} NodeObj;

// private Node type
typedef NodeObj *Node;

// private ListObj type
typedef struct ListObj
{
   Node front;
   Node back;
   Node cursor;
   int cursorIndex;
   int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data)
{
   Node N = malloc(sizeof(NodeObj));
   assert(N != NULL);
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node *pN)
{
   if (pN != NULL && *pN != NULL)
   {
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void)
{
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->cursorIndex = -1;
   return (L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List *pL)
{
   if (pL != NULL && *pL != NULL)
   {
      while (!isEmpty(*pL))
      {
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

// front()
// Returns the value at the front of L.
// Pre: length()>0
int front(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if (length(L) == 0)
   {
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return (L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: length()>0
int back(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if (length(L) == 0)
   {
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return (L->back->data);
}

// length()
// Returns the length of L.
int length(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling getLength() on NULL List reference\n");
      exit(1);
   }
   return (L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling getLength() on NULL List reference\n");
      exit(1);
   }
   if (L->cursor == NULL)
   {
      return -1;
   }
   return L->cursorIndex;
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if (length(L) <= 0)
   {
      printf("List Error: calling get() on an empty List\n");
      exit(1);
   }
   return L->cursor->data;
}

// equals()
// returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B)
{
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if (A == NULL || B == NULL)
   {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   eq = (A->length == B->length);
   N = A->front;
   M = B->front;
   while (eq && N != NULL)
   {
      eq = (N->data == M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return (L->length == 0);
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   while (L->front != NULL)
   {
      deleteFront(L);
   }
   L->cursor = NULL;
   L->length = 0;
   L->cursorIndex = -1;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if (isEmpty(L))
   {
      return;
   }
   L->cursor = L->front;
   L->cursorIndex = 0;
}

// moveBack()
// If L is non-empty, sets cursor under the back element.
// otherwise, does nothing.
void moveBack(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling moveBack() on NULL List reference.\n");
      exit(1);
   }
   if (isEmpty(L))
   {
      return;
   }
   L->cursor = L->back;
   L->cursorIndex = L->length - 1;
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling movePrev() on NULL List reference.\n");
      exit(1);
   }
   if (L->cursorIndex != -1)
   {
      if (L->cursor != NULL)
      {
         L->cursor = L->cursor->prev;
         L->cursorIndex--;
      }
      else
      {
         L->cursor = L->cursor->prev;
         L->cursorIndex = -1;
      }
   }
   return;
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling movePrev() on NULL List reference.\n");
      exit(1);
   }
   if (L->cursorIndex != -1)
   {
      if (L->cursor != NULL)
      {
         L->cursor = L->cursor->next;
         L->cursorIndex++;
      }
      else
      {
         L->cursor = L->cursor->next;
         L->cursorIndex = -1;
      }
   }
   return;
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data)
{
   Node N = newNode(data);
   Node P = NULL;
   if (L == NULL)
   {
      printf("List Error: calling prepend() on NULL List reference.\n");
      exit(1);
   }
   if (isEmpty(L))
   {
      L->front = L->back = N;
   }
   else
   {
      P = L->front;
      L->front = N;
      L->front->next = P;
      N->next->prev = N;
   }
   if (L->cursorIndex != -1)
   {
      L->cursorIndex++;
   }
   L->length++;
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int data)
{
   Node N = newNode(data);
   Node P = NULL;
   if (L == NULL)
   {
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   if (isEmpty(L))
   {
      L->front = L->back = N;
   }
   else
   {
      P = L->back;
      L->back->next = N;
      L->back = N;
      L->back->prev = P;
   }
   L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data)
{
   Node N = newNode(data);
   Node P = NULL;

   if (L == NULL)
   {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if ((length(L) > 0) && (index(L) >= 0))
   {
      if (index(L) == 0)
      {
         P = L->front;
         L->front = N;
         L->front->next = P;
         N->next->prev = N;
      }
      else
      {
         P = L->cursor->prev;
         L->cursor->prev = N;
         N->next = L->cursor;
         N->prev = P;
         P->next = N;
      }
   }
   if (L->cursorIndex != -1)
   {
      L->cursorIndex++;
   }
   L->length++;
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
   Node N = newNode(data);
   Node P = NULL;
   if (L == NULL)
   {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if ((length(L) > 0) && (index(L) >= 0))
   {
      if (index(L) == (length(L) - 1))
      {
         P = L->back;
         L->back->next = N;
         L->back = N;
         L->back->prev = P;
      }
      else
      {
         P = L->cursor->next;
         L->cursor->next = N;
         N->next = P;
         N->next->prev = N;
      }
   }
   L->length++;
}

// deleteFront()
// Delete the front element of L.
// Pre: length()>0
void deleteFront(List L)
{
   Node N = NULL;

   if (L == NULL)
   {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if (length(L) == 0)
   {
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(1);
   }
   N = L->front;
   if (length(L) > 1)
   {
      L->front = L->front->next;
      L->front->prev = NULL;
   }
   if (length(L) == 1)
   {
      L->front = L->back = NULL;
   }
   if (L->cursorIndex != -1)
   {
      L->cursorIndex--;
   }
   L->length--;
   freeNode(&N);
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
   Node N = NULL;

   if (L == NULL)
   {
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if (length(L) == 0)
   {
      printf("List Error: calling deleteBack on an empty List\n");
      exit(1);
   }
   N = L->back;

   if (L->cursor == L->back)
   {
      L->cursorIndex = -1;
   }

   if (length(L) > 1)
   {
      L->back = L->back->prev;
      L->back->next = NULL;
   }
   else
   {
      L->front = L->back = NULL;
   }
   L->length--;
   freeNode(&N);
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete (List L)
{
   Node N = NULL;
   Node P = NULL;
   if (L == NULL)
   {
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   // If list is of length 1
   if ((length(L) == 1) && (index(L) >= 0))
   {
      N = L->cursor;
      L->front = L->back = NULL;
      L->cursorIndex = -1;
      L->cursor = NULL;
   }
   if ((length(L) > 1) && (index(L) >= 0))
   {
      // If cursor is at the front
      if (index(L) == 0)
      {
         N = L->front;
         L->front = L->front->next;
         L->front->prev = NULL;
      }
      // If cursor is at the back
      else if (index(L) == (length(L) - 1))
      {
         N = L->back;
         L->back = L->back->prev;
         L->back->next = NULL;
      }
      // Cursor is at the middle of the list
      else
      {
         N = L->cursor;
         P = L->cursor->prev;
         P->next = L->cursor->next;
         P->next->prev = P;
      }
   }
   freeNode(&N);
   L->cursor = NULL;
   L->cursorIndex = -1;
   L->length--;
}

// Other Functions ------------------------------------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE *out, List L)
{
   Node N = NULL;

   if (L == NULL)
   {
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }

   for (N = L->front; N != NULL; N = N->next)
   {
      fprintf(out, "%d ", N->data);
   }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L)
{
   Node N = NULL;
   List R = newList();

   if (L == NULL)
   {
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(1);
   }
   if (isEmpty(L))
   {
      return R;
   }

   append(R, L->front->data);
   moveFront(R);

   for (N = L->front->next; N != NULL; N = N->next)
   {
      insertAfter(R, N->data);
      moveNext(R);
   }

   R->cursor = NULL;
   R->cursorIndex = -1;
   return R;
}

// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B)
{
   if (A == NULL || B == NULL)
   {
      printf("List Error: calling concatList on empty List reference\n");
      exit(1);
   }
   List C = copyList(A);

   Node N = newNode(B->front->data);
   append(C, B->front->data);
   moveBack(C);

   for (N = B->front->next; N != NULL; N = N->next)
   {
      insertAfter(C, N->data);
      moveNext(C);
   }

   C->cursor = NULL;
   C->cursorIndex = -1;
   return C;
}
