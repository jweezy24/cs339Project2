#include "queueStruct.c"
#include <stdio.h>
#include <stdlib.h>

queue packets;

void init_queue(queue* packets){
  packets = createQueue(100);
}
