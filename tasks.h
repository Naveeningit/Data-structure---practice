#ifndef TASKS_H
#define TASKS_H

void Add(void* arg);
void Sub(void* arg);
// Add more as needed

typedef struct {
	int a, b;
} Args;

#endif
void Add(void* arg) {
	Args* data = (Args*)arg;
	printf("[Task: Add] %d + %d = %d\n", data->a, data->b, data->a + data->b);
	//free(data); // Don't forget to free!
}

void Sub(void* arg) {
	Args* data = (Args*)arg;
	printf("[Task: Sub] %d - %d = %d\n", data->a, data->b, data->a - data->b);
//	free(data);
}
