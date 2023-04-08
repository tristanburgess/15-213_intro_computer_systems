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
    if (q == NULL) {
      return NULL;
    }
  
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
  
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
      return;
    }

    list_ele_t *cur = q->head;
    while (cur != NULL) {
      list_ele_t *tmp = cur;
      cur = cur->next;
      free(tmp->value);
      free(tmp);
    }

    /* Free queue structure */
    free(q);
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
    list_ele_t *newh;
    if (q == NULL || s == NULL) {
      return false;
    }
  
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
      return false;
    }
  
    size_t slen = strlen(s) + 1;
    char *newh_val = malloc(slen);
    if (newh_val == NULL) {
      free(newh);
      return false;
    }
    strncpy(newh_val, s, slen);
  
    newh->value = newh_val;
    newh->next = q->head;
    q->head = newh;
    q->size++;
    if (q->size == 1) {
      q->tail = q->head;
    }
  
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
    list_ele_t *newt;
    if (q == NULL || s == NULL) {
      return false;
    }

    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
      return false;
    }

    size_t slen = strlen(s) + 1;
    char *newt_val = malloc(slen);
    if (newt_val == NULL) {
      free(newt);
      return false;
    }
    strncpy(newt_val, s, slen);
  
    newt->value = newt_val;
    newt->next = NULL;
    if (q->tail != NULL) {
      q->tail->next = newt;
    }
    q->tail = newt;
    q->size++;
    if (q->size == 1) {
      q->head = q->tail;
    }
  
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
    if (q == NULL || q->size == 0) {
      return false;
    }
  
    list_ele_t *newh = q->head->next;
  
    if (sp != NULL) {
      strncpy(sp, q->head->value, bufsize);
      sp[bufsize - 1] = '\0';
    }
  
    free(q->head->value);
    free(q->head);
    q->head = newh;
    q->size--;
  
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
  if (q == NULL) {
    return 0;
  }

  return q->size;
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
  if (q == NULL || q->size == 0) {
    return;
  }

  list_ele_t *p = NULL;
  list_ele_t *c = NULL;
  list_ele_t *n = q->head;

  q->tail = n;

  while (n != NULL) {
    p = c;
    c = n;
    n = c->next;
    c->next = p;
  }

  q->head = c;
}

