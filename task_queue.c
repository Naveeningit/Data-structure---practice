// Task queue
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "tasks.h"

#define MAX_QUEUE_SIZE 3
#define NUM_TASKS 3
int producer_done=0;
typedef struct {
	void (*function)(void*);
	void* arg;
	int task_id;
} Task;

typedef struct {
	Task tasks[MAX_QUEUE_SIZE];
	int front, rear, count;
	pthread_mutex_t lock;
	pthread_cond_t not_empty;
	pthread_cond_t not_full;
} TaskQueue;

TaskQueue queue = {
	.front = 0, .rear = 0, .count = 0,
	.lock = PTHREAD_MUTEX_INITIALIZER,
	.not_empty = PTHREAD_COND_INITIALIZER,
	.not_full = PTHREAD_COND_INITIALIZER
};

void enqueue(Task t) {
	pthread_mutex_lock(&queue.lock);
	while (queue.count == MAX_QUEUE_SIZE) {
		printf("Queue is full\n");
		pthread_cond_wait(&queue.not_full, &queue.lock);
		return;
	}

	queue.tasks[queue.rear] = t;
	queue.rear = (queue.rear + 1) % MAX_QUEUE_SIZE;
	queue.count++;

	pthread_cond_signal(&queue.not_empty);
	pthread_mutex_unlock(&queue.lock);
}

Task dequeue() {
	pthread_mutex_lock(&queue.lock);
	while (queue.count == 0)
		pthread_cond_wait(&queue.not_empty, &queue.lock);

	Task t = queue.tasks[queue.front];
	queue.front = (queue.front + 1) % MAX_QUEUE_SIZE;
	queue.count--;

	pthread_cond_signal(&queue.not_full);
	pthread_mutex_unlock(&queue.lock);
	return t;
}

void* producer(void* arg) {
	int choice;
	for (int task_id = 1; task_id <= NUM_TASKS; task_id++) {
		printf("\nEnter task %d (1:Add, 2:Sub): ", task_id);
		scanf("%d", &choice);

		Task newtask;
		newtask.task_id=task_id;
		Args* data = (Args*)malloc(sizeof(Args));

		if (choice == 1) {
			printf("Enter two numbers: ");
			scanf("%d %d", &data->a, &data->b);

			newtask.function = Add;
		}
		else if (choice == 2) {
			printf("Enter two numbers: ");
			scanf("%d %d", &data->a, &data->b);

			newtask.function = Sub;
		}
		else {
			printf("Invalid task. Skipping.\n");
			free(data);
			continue;
		}

		newtask.arg = data;
		enqueue(newtask);
		//	sleep(1);
	}
	producer_done=1;
	pthread_exit(NULL);
	return NULL;
}

void* consumer(void* arg) {
	while (1) {
		pthread_mutex_lock(&queue.lock);

		// Check for exit condition before waiting
		while (queue.count == 0) {
			if (producer_done) {
				pthread_mutex_unlock(&queue.lock);
				printf("Consumer received termination signal. Exiting.\n");
				return NULL;
			}
			pthread_cond_wait(&queue.not_empty, &queue.lock);
		}

		// Dequeue safely
		Task t = queue.tasks[queue.front];
		queue.front = (queue.front + 1) % MAX_QUEUE_SIZE;
		queue.count--;

		pthread_cond_signal(&queue.not_full);
		pthread_mutex_unlock(&queue.lock);

		// Execute task outside lock
		printf("\nTask %d in Execution\n", t.task_id);
		t.function(t.arg);
		free(t.arg); // Avoid memory leak
		sleep(2);    // Simulate processing delay
	}
}

int main() {
	pthread_t prod, cons;
	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);


	pthread_join(prod, NULL);
	// You can cancel or terminate the consumer after all tasks are done
//	pthread_cancel(cons);
	pthread_join(cons, NULL);
	return 0;
}
