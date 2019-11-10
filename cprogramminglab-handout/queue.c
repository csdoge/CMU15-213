/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q == NULL)   return NULL;
    q->head = NULL;
    q -> tail = NULL;
    q -> size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if(q == NULL)   return;
    list_ele_t *p = q -> head, *cur;
    while(p != NULL)
    {
      cur = p;
      p = p -> next;
      free(cur -> value);   //need to free string values
      free(cur);
    }
    free(q);
    q -> head = NULL;
    q -> tail = NULL;
    q -> size = 0;
    q = NULL;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if(q == NULL)  return false;
    int length = strlen(s) + 1;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if(newh == NULL)  return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    
    newh -> value = malloc(length * sizeof(char));
    for(int i = 0; i < length -1; i++)
    {
      newh -> value[i] = s[i];
    }
    newh -> value[length - 1] = '\0';
    if(q -> size == 0)  q -> tail = newh;
    q -> size += 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if(q == NULL) return false;
    int length = strlen(s) + 1;
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if(newt == NULL)  return false;
    if(q -> tail == NULL)
    {
      q -> head = newt;
      q -> tail = newt;
    }
    else
    {
      q -> tail -> next = newt;
      q -> tail = newt;
    }
    newt -> next = NULL;
    newt -> value = malloc(length * sizeof(char));
    for(int i = 0; i < length - 1; i++)
    {
      newt -> value[i] = s[i];
    }
    newt -> value[length - 1] = '\0';
    q -> size += 1;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if(q == NULL || q -> head == NULL)  return false;
    list_ele_t *to_rem = q -> head;
    int length = strlen(to_rem -> value) + 1;
    //list_ele_t *to_rem = q -> head;
    if(length > bufsize)
    {
      sp = malloc(bufsize * sizeof(char));
      for(int i = 0; i < bufsize - 1; i++)
        sp[i] = to_rem -> value[i];
      sp[bufsize - 1] = '\0';

    }
    else
    {
      sp = malloc(length * sizeof(char));
      for(int i = 0; i < length - 1; i++)
        sp[i] = to_rem -> value[i];
      sp[length - 1] = '\0';
    }
    q->head = q->head->next;
    q -> size -= 1;
    free(to_rem -> value);
    free(to_rem);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if(q == NULL)   return false;
    return q -> size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if(q == NULL || q -> head == NULL || q -> tail == NULL) return;
    list_ele_t *old_head = q -> head;
    list_ele_t *old_tail = q -> tail;
    list_ele_t *a = q -> head;
    list_ele_t *b = q -> head -> next;
    list_ele_t *c = q -> head -> next -> next;

    b -> next = a;
    a -> next = NULL;
    while(c != NULL)
    {
      a = b;
      b = c;
      c = c -> next;
      b -> next = a;
    }
    q -> head = old_tail;
    q -> tail = old_head;
}

