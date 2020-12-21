//-----------------------------------------------------------------------------
// Dictionary.c
// Linked List implementation of the Dictionary ADT.
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

// Private Types and Functions ------------------------------------------------

// NodeObj
typedef struct NodeObj
{
   char *key;   // unique identifier for the pair
   char *value; // contents which are paired with a unique identifier
   struct NodeObj *next;
} NodeObj;

// Node
typedef NodeObj *Node;

// newNode()
// Constructor for private Node type.
Node newNode(char *k, char *v)
{
   Node N = malloc(sizeof(NodeObj));
   assert(N != NULL);
   N->next = NULL;
   N->key = k;
   N->value = v;
   return N;
}

// freeNode()
// Destructor for private Node type
void freeNode(Node *pN)
{
   if (pN != NULL && *pN != NULL)
   {
      free(*pN);
      *pN = NULL;
   }
}

// DictionaryObj
typedef struct DictionaryObj
{
   Node head; // the starting point of a linked list
   int items; // keeping count of items
} DictionaryObj;

// findKey()
// Returns a reference to the Node with the same key, else returns NULL
Node findKey(Dictionary D, char *k)
{
   Node N = D->head;
   if (N == NULL)
   {
      return N;
   }
   else
   {
      for (int i = 0; i < D->items; i++)
      {
         if (strcmp((N->key), k) == 0)
         {
            return N;
         }
         N = N->next;
      }
   }
   return N;
}

// countChars()
// Returns the number of characters in a text representation of D. Used by
// DictionaryToString() to allocate sufficient heap memory.  Does not count
// the terminating null '\0' character.
int countChars(Dictionary D)
{
   int kcount = 0;
   int vcount = 0;
   int count = 0;
   Node N = D->head;
   for (int i = 0; i < D->items; i++)
   {
      kcount += strlen(N->key) + 1;   // all all the string lengths and the
      vcount += strlen(N->value) + 1; // spaces in between
      N = N->next;
   }
   count = vcount + kcount;
   return count;
}

// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Constructor for the Dictionary type.
Dictionary newDictionary()
{
   Dictionary D = malloc(sizeof(DictionaryObj));
   D->head = NULL;
   D->items = 0;
   return D;
}

// freeDictionary()
// Destructor for the Dictionary type.
void freeDictionary(Dictionary *pD)
{
   if (pD != NULL && *pD != NULL)
   {
      makeEmpty(*pD);
      free(*pD);
      *pD = NULL;
   }
}

// ADT operations -------------------------------------------------------------

// size()
// Returns the number of elements in D.
int size(Dictionary D)
{
   if (D == NULL)
   {
      fprintf(stderr,
              "Dictionary Error: calling size() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return D->items; // sums the number of nodes linked together until reaches the end
}

// lookup()
// If D contains a pair whose key matches argument k, then return the
// corresponding value, otherwise return NULL.
char *lookup(Dictionary D, char *k)
{
   Node N = NULL;
   if (D == NULL)
   {
      fprintf(stderr,
              "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   else
   {
      N = D->head;
      for (int i = 0; i < D->items; i++)
      {
         if (strcmp((N->key), k) == 0)
         {
            return N->value;
         }
         N = N->next;
      }
   }
   return NULL;
}

// insert()
// Insert the pair (k,v) into D.
// Pre: lookup(D, k)==NULL (D does not contain a pair whos first memeber is k.)
void insert(Dictionary D, char *k, char *v)
{
   Node N = NULL;
   Node P = NULL;
   Node C = NULL;
   if (D == NULL)
   {
      fprintf(stderr,
              "Dictionary Error: calling add() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if (lookup(D, k) != NULL) // check if key already exists
   {
      fprintf(stderr,
              "Dictionary Error: calling insert() on D that already contains key inputted");
      exit(EXIT_FAILURE);
   }
   N = newNode(k, v);
   if (D->head == NULL) // only one item in the list
   {
      D->head = N;
   }
   else // >=1 items in the list
   {
      P = D->head;
      while (P->next != NULL)
      {
         P = P->next;
      }
      P->next = N;
   }
   (D->items)++;
}

// delete()
// Deletes string from position index.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete (Dictionary D, char *k)
{
   Node N = NULL, P = NULL;
   if (D == NULL)
   {
      fprintf(stderr,
              "Dictionary Error: calling delete() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if (lookup(D, k) == NULL)
   {
      fprintf(stderr,
              "Dictionary Error: calling delete() on key that does not exit\n");
      exit(EXIT_FAILURE);
   }
   if (D->head == NULL)
   {
      fprintf(stderr,
              "Dictionary Error: calling delete() on empty Dictionary\n");
      exit(EXIT_FAILURE);
   }

   N = D->head;
   if (strcmp((N->key), k) == 0)
   {
      P = D->head;
      D->head = D->head->next;
      freeNode(&P);
   }
   else
   {
      while ((N != NULL) && (N->next != NULL))
      {
         if (strcmp((N->next->key), k) == 0)
         {
            P = N->next;
            N->next = N->next->next;
            freeNode(&P);
         }
         N = N->next;
      }
   }
   (D->items)--;
}
//    N = D->head;
//    if ((D->head->next == NULL) && !(strcmp((D->head->key), k))) // only one item in list
//    {
//       freeNode(&N);
//       D->head = NULL;
//    }
//    else // > || = 2 items in the list
//    {
//       if (D->items > 2)
//       {
//          while (N->next != NULL && N->next->next != NULL)
//          {
//             if (!strcmp((N->next->key), k))
//             {
//                C = N; // before value that will be removed
//                break;
//             }
//             N = N->next;
//          }
//          P = C->next; // node to be removed
//          N = P->next; // node that will be glued to C
//          C->next = N;
//          P->next = NULL;
//          freeNode(&P);
//       }
//       else
//       {
//          if(!strcmp(N->next->key,k)){
//             P = N->next; // node after the one that will be removed
//             D->head = P;
//             N->next = NULL;
//             freeNode(&N);
//          }
//       }
//    }
// }

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D)
{
   if (D == NULL)
   {
      fprintf(stderr,
              "Dictionary Error: calling deleteAll() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if (D->items == 0)
   {
      fprintf(stderr,
              "Dictionary Error: calling deleteAll() on empty Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   Node N = D->head;
   Node P;
   while (N != NULL)
   {
      P = N;
      N = N->next;
      freeNode(&P);
      (D->items)--;
   }
   D->head = NULL;
}

// Other Operations -----------------------------------------------------------

// DictionaryToString()
// Determines a text representation of the current state of Dictionary D. Each
// (key, value) pair is represented as the chars in key, followed by a space,
// followed by the chars in value, followed by a newline '\n' char. The pairs
// occur in the same order they were inserted into D. The function returns a
// pointer to a char array, allocated from heap memory, containing the text
// representation described above, followed by a terminating null '\0' char.
// It is the responsibility of the calling function to free this memory.
char *DictionaryToString(Dictionary D)
{
   int i;
   int count;
   char *str;
   Node N;
   if (D == NULL)
   {
      fprintf(stderr,
              "Dictionary Error: calling DictionaryToString() on NULL Dictionary "
              "reference\n");
      exit(EXIT_FAILURE);
   }
   N = D->head;

   count = countChars(D);
   i = 0;
   str = calloc(count + 1, sizeof(char));
   N = D->head;
   while (N != NULL)
   {
      strcpy(str + i, N->key);
      i += strlen(N->key);
      str[i] = ' ';
      i++;
      strcpy(str + i, N->value);
      i += strlen(N->value);
      N = N->next;
      str[i] = '\n';
      i++;
   }
   if ((D->items) > 0)
      i--;
   str[i] = '\0'; // overwrite last space with terminating null '\0'

   return str;
}