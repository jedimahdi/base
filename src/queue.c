#include "containers/queue.h"

void queue_enqueue(Queue *queue, QNode *node) {
  assert(node != NULL);

  if (queue->count == 0) {
    queue->beg = queue->end = node;
  } else {
    queue->end->next = node;
    queue->end = node;
  }
  queue->count++;
}

QNode *queue_dequeue(Queue *queue) {
  if (queue->count == 0) {
    return NULL;
  }
  QNode *node = queue->beg;
  if (queue->count == 1) {
    queue->beg = queue->end = NULL;
  } else {
    queue->beg = queue->beg->next;
  }
  queue->count--;
  return node;
}
