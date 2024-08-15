#ifndef QUEUE_H_
#define QUEUE_H_

#include "defines.h"

typedef struct QNode QNode;

struct QNode {
  QNode *next;
};

typedef struct {
  QNode *beg;
  QNode *end;
  usize count;
} Queue;

void queue_enqueue(Queue *queue, QNode *node);
QNode *queue_dequeue(Queue *queue);

#endif // QUEUE_H_
