
/* 
 * Author: Surya Keswani 
 * Contact: sukeswan@ucsc.edu
 * School: University of California, Santa Cruz
 * Date: November 2018
 */
#include <stdlib.h>
#include <stdio.h>
#include "List.h"

// make the node structure 

typedef struct NodeObj {
    struct NodeObj* next;
    struct NodeObj* previous;
    int data;
} NodeObj;

typedef struct NodeObj* Node;
// make list structure 

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;

} ListObj;
// Constructors-destructor 

// make a new node by allocating memory

// make new node

Node newNode(int data) {
    // allocate memory 
    Node node = malloc(sizeof (NodeObj));
    // default data and pointers
    node->data = data;
    node->next = NULL;
    node->previous = NULL;
    return node;
}
// free node memory

void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}
// make a new list by allocating memory 

List newList(void) {
    List list = malloc(sizeof (ListObj));
    list->front = NULL;
    list->back = NULL;
    list->cursor = NULL;
    list->index = -1;
    list->length = 0;
    return list;
}
// free all the nodes in the list then the list itself 

void freeList(List* pL) {

    if (pL != NULL && *pL != NULL) {
        /*
        while (pL->length > 0) {
            deleteFront(*pL);
        }*/
        clear(*pL);
        free(*pL);
        *pL = NULL;

    }
}

// Access functions 
// return length of the list

int length(List L) {
    if (L == NULL) {

        printf("List Error: length() called on NULL List");
        exit(1);
    }
    return (L->length);
}
// return index of the cursor

int index(List L) {
    if (L == NULL) {
        printf("List Error: index() called on NULL List");
        exit(1);
    }
    return L->index;
}
// get data at front node

int front(List L) {
    if (L == NULL) {
        printf("List Error: front() called on NULL List");
        exit(1);
    }
    if (L->length < 1) {

        printf("List Error: front() called on empty List");
        exit(1);
    }
    return L->front->data;
}
// get data at back node

int back(List L) {
    if (L == NULL) {
        printf("List Error: back() called on NULL List");
        exit(1);
    }
    if (L->length < 1) {

        printf("List Error: back() called on empty List");
        exit(1);
    }
    return L->back->data;
}
// the the data at the cursor

int get(List L) {
    if (L == NULL) {
        printf("List Error: get() called on NULL List");
        exit(1);
    }
    if (L->length < 1) {
        printf("List Error: get() called on empty List");
        exit(1);

    }
    if (L->index < 0) {

        printf("List Error: get() called on List with undefined cursor");
        exit(1);

    }
    return L->cursor->data;
}
// check if 2 lists are equal 

int equals(List A, List B) {
    if (A == NULL) {
        printf("List Error: get() called on NULL List (A)");
        exit(1);
    }
    if (B == NULL) {
        printf("List Error: get() called on NULL List(B)");
        exit(1);
    }
    // if they lists are not the same size they are not equal
    if (A->length != B->length) {
        return 0;
    }

    // iterate through each list comparing the nodes
    Node pOne = A->front;
    Node pTwo = B->front;

    for (int i = 0; i < A->length; i++) {
        //if they are not the same return false
        if (pOne->data != pTwo->data) {

            return 0;

        }
        // move to the next nodes
        pOne = pOne->next;
        pTwo = pTwo->next;

    }
    return 1;
}
// Manipulation procedures 
// clear list reset to original state

void clear(List L) {
    if (L == NULL) {
        printf("List Error: clear() called on NULL List");
        exit(1);
    }
    // delete all the nodes in the list then free it
    while (length(L) > 0) {
        //printf("%d", length(L));
        deleteFront(L);
    }
    // reset list to original state
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->index = -1;
    L->length = 0;
}
// move cursor to the front node

void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: moveFront() called on NULL List ");
        exit(1);
    }
    if (L->length <= 0) {
        printf("List Error: moveFront() called on empty List");
        exit(1);
    }
    // move cursor to front node of the index
    L->index = 0;
    L->cursor = L->front;
}
// move cursor to the back node

void moveBack(List L) {
    if (L == NULL) {
        printf("List Error: moveBack() called on NULL List");
        exit(1);
    }
    if (L->length <= 0) {

        printf("Lister Error: moveBack() called on empty List");
        exit(1);
    }
    // move cursor to back node of the index
    L->index = L->length - 1;
    L->cursor = L->back;
}
// move cursor towards the front

void movePrev(List L) {
    if (L == NULL) {
        printf("List Error: movePrev() called on NULL List");
        exit(1);
    }
    // move the cursor towards the front 
    if (L->index > 0) {
        L->index--;
        L->cursor = L->cursor->previous;
    }// if the cursor is the front node make it undefined 
    else {

        L->index = -1;
        L->cursor = NULL;
    }
}
// move cursor towards the back

void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: moveNext() called on NULL List");
        exit(1);
    }
    //if the cursor is not the back and defined
    if (L->index < L->length - 1 && L->index >= 0) {
        L->index++;
        L->cursor = L->cursor->next;
    } else {
        // otherwise cursor is undefined 

        L->index = -1;
        L->cursor = NULL;
    }
}
// add node to front of the list

void prepend(List L, int data) {
    if (L == NULL) {
        printf("List Error: prepend() called on NULL List");
        exit(1);
    }
    if (L->length > 0) {
        // make new front node
        Node NewFront = newNode(data);
        // have it point to the original front and NULL
        NewFront->next = L->front;
        NewFront->previous = NULL;
        //set original front to point to new front
        L->front->previous = NewFront;
        // front node now is new front node
        L->front = NewFront;
        if (index(L) > -1) {
            L->index++;
        }
    }// the list is empty
    if (L->length == 0) {
        // make new front node and set back and front to NUL

        L->front = newNode(data);
        L->front->previous = NULL;
        L->front->next = NULL;
        L->back = L->front;
    }
    L->length++;
}
// add node to the back of list 

void append(List L, int data) {
    if (L == NULL) {
        printf("List Error: append() called on NULL List");
        exit(1);
    }
    if (L->length > 0) {
        // make new back node and set front and back
        Node pNewBack = newNode(data);
        pNewBack->previous = L->back;
        pNewBack->next = NULL;
        // set original back to  point to new back
        L->back->next = pNewBack;
        // set back to point to new back 
        L->back = pNewBack;

    }// if the list is empty
    else {
        // make new back node and set its next and previous

        L->back = newNode(data);
        L->back->next = NULL;
        L->back->previous = NULL;
        // make back = previous node
        L->front = L->back;
    }
    L->length++;
}
//insert node before the cursor

void insertBefore(List L, int data) {
    if (L == NULL) {
        printf("List Error: insertBefore() called on NULL List");
        exit(1);
    }
    if (L->length < 1) {
        printf("List Error: insertBefore() called on an Empty List");
        exit(1);
    }
    if (L->index < 0) {
        printf("List Error: insertBefore() called with undefined cursor");
        exit(1);
    }
    // in cursor is at the front then just prepend new data
    if (L->index == 0) {
        prepend(L, data);
    }// otherwise add it before cursor
    else {
        // make new node and set its next and previous nodes

        Node n = newNode(data);
        n->next = L->cursor;
        n->previous = L->cursor->previous;
        // patch the new node into the Linked List 
        L->cursor->previous->next = n;
        L->cursor->previous = n;
        // increment length and index
        L->length++;
        L->index++;
    }
}
// insert node after cursor 

void insertAfter(List L, int data) {
    if (L == NULL) {
        printf("List Error: insertAfter() called on NULL List");
        exit(1);
    }
    if (L->length < 1) {
        printf("List Error: insertAfter() called on an Empty List");
        exit(1);
    }
    if (L->index < 0) {
        printf("List Error: insertAfter() called with undefined cursor");
        exit(1);
    }
    // in cursor is at the back then just append new data
    if (L->index == L->length - 1) {
        append(L, data);
    } else {
        //make new node and set previous and next

        Node n = newNode(data);
        n->next = L->cursor->next;
        n->previous = L->cursor;
        //patch new Node into Linked List
        L->cursor->next->previous = n;
        L->cursor->next = n;
        // increase length by 1
        L->length++;
    }

}
// delete the front node in the list

void deleteFront(List L) {
    if (L == NULL) {
        printf("List Error: deleteFront() called on NULL List");
        exit(1);
    }
    if (L->length < 1) {
        printf("List Error: deleteFront() called on empty List");
        exit(1);
    }
    if (L->length == 1) {
        Node temp = L->front;
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
        L->length = 0;
        freeNode(&temp);
    } else {
        // if cursor is at the front make it undefined
        if (L->index == 0) {
            L->index = -1;
            L->cursor = NULL;
        }
        // delete the front node
        Node temp = L->front;
        L->front = L->front->next;
        L->front->previous = NULL;
        L->length--;
        freeNode(&temp);
        //if cursor is front element that index is already set to -1 above.
        //You do not want to decrement it again to -2
        if (L->index >= 0) {
            L->index--;
        }
    }
}
// delete the back node in the list

void deleteBack(List L) {
    if (L == NULL) {
        printf("List Error: deleteBack() called on NULL List");
        exit(1);
    }
    if (L->length < 1) {
        printf("List Error: deleteBack() called on empty List");
        exit(1);
    }
    // if there is only one element in the list clear the list
    if (L->length == 1) {
        // reset list to original state
        Node temp = L->back;
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
        L->length = 0;
        // free the node
        freeNode(&temp);
        return;
    }
    // make cursor undefined if at the back
    if (L->index == L->length - 1) {

        L->index = -1;
        L->cursor = NULL;

    }
    Node temp = L->back;
    // move back node to second to last node
    L->back = L->back->previous;
    // set back to point to null
    L->back->next = NULL;
    // decrease the length 
    L->length--;
    freeNode(&temp);
}
// delete cursor element 

void delete(List L) {
    if (L == NULL) {
        printf("List Error: delete() called on NULL List");
        exit(1);
    }
    if (L->length < 1) {
        printf("List Error: delete() called on empty List");
        exit(1);
    }
    if (L->index < 0) {
        printf("List Error: delete() called with undefined cursor");
        exit(1);
    }
    if (L->index == 0) {
        deleteFront(L);
        return;
    }
    if (L->index == L->length - 1) {
        deleteBack(L);

        return;
    }
    // connect cursor previous to cursor next
    Node temp = L->cursor;
    L->cursor->previous->next = L->cursor->next;
    L->cursor->next->previous = L->cursor->previous;
    //decrease length and make cursor undefined 
    L->length--;
    L->cursor = NULL;
    L->index = -1;
    freeNode(&temp);
}

// Other operations Ï

// print the list 

void printList(FILE* out, List L) {

    Node N = NULL;

    if (L == NULL) {
        printf("Queue Error: calling printQueue() on NULL Queue reference\n");
        exit(1);
    }

    for (N = L->front; N != NULL; N = N->next) {

        fprintf(out, "%d ", N->data);
    }
}
// copy list to new list and return it

List copyList(List L) {
    // make a new list
    List list = newList();
    // traverse through list copying each node into the new list
    Node current = L->front;
    for (int i = 0; i < L->length; i++) {

        append(list, current->data);
        current = current->next;
    }
    // return new List 
    return list;
}
// add 2 lists together 

List concatList(List A, List B) {
    Node current = B->front;
    // add all the data in B to the list in A
    for (int i = 0; i < B->length; i++) {
        append(A, current->data);
    }
    // make cursor undefined
    A->cursor = NULL;
    A->index = -1;
    //return list a
    return A;
}