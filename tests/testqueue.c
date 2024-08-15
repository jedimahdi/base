#include "ds/queue.h"
#include <criterion/criterion.h>

typedef struct {
  QNode qnode;
  i32 value;
} Item;

Test(queue, basic) {
  Queue q = {0};

  Item item1 = {.value = 11};
  Item item2 = {.value = 14};
  Item item3 = {.value = 19};
  Item item4 = {.value = 99};

  queue_enqueue(&q, &item1.qnode);
  queue_enqueue(&q, &item2.qnode);
  queue_enqueue(&q, &item3.qnode);

  Item *q1 = container_of(queue_dequeue(&q), Item, qnode);
  Item *q2 = container_of(queue_dequeue(&q), Item, qnode);
  Item *q3 = container_of(queue_dequeue(&q), Item, qnode);

  queue_enqueue(&q, &item4.qnode);
  Item *q4 = container_of(queue_dequeue(&q), Item, qnode);

  cr_expect(q1->value == item1.value);
  cr_expect(q2->value == item2.value);
  cr_expect(q3->value == item3.value);
  cr_expect(q4->value == item4.value);
}
