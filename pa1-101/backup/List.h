//-----------------------------------------------------------------------------
// Brandon Delgado, bdelgad3
// 2020 Spring CSE101 PA1
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Creates and returns an empty List. 
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// front()
// Returns the value at the front of L.
// Pre: length()>0
int front(List L);

// back()
// Returns the value at the back of L.
// Pre: length()>0
int back(List L);

// length()
// Returns the length of L.
int length(List L);

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L);

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L);

// equals()
// returns true (1) iff Lists A and B are in same 
// state, and returns false (0) otherwise.
int equals(List A, List B);

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L);


// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L);

// moveFront()
// If L is non-empty, sets cursor under the front element, 
// otherwise does nothing.
void moveFront(List L);

// moveBack()
// If L is non-empty, sets cursor under the back element.
// otherwise, does nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, move cursor one 
// step toward the front of L; if cursor is defined and at 
// front, cursor becomes undefined; if cursor is undefined 
// do nothing
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one 
// step toward the back of L; if cursor is defined and at 
// back, cursor becomes undefined; if cursor is undefined 
// do nothing
void moveNext(List L);

// prepend()
// Insert new element into L. If L is non-empty, 
// insertion takes place before front element.
void prepend(List L, int data);

// append()
// Insert new element into L. If L is non-empty, 
// insertion takes place after back element.
void append(List L, int data);

// insertBefore()
// Insert new element before cursor. 
// Pre: length()>0, index()>=0
void insertBefore(List L, int data);

// insertAfter()
// Insert new element after cursor. 
// Pre: length()>0, index()>=0
void insertAfter(List L, int data);

// deleteFront()
// Delete the front element of L.
// Pre: length()>0
void deleteFront(List L);

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined. 
// Pre: length()>0, index()>=0
void delete(List L);



// Other Functions ------------------------------------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers, 
// with front on left.
void printList(FILE* out, List L);

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state 
// of L is unchanged.
List copyList(List L); 

// Returns a new List which is the concatenation of 
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B. 
// The states of A and B are unchanged.
List concatList(List A, List B);

#endif
