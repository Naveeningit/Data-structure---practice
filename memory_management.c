// Memory Management Using Stack
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    void* address;     // pointer to the allocated memory
    size_t size;       // size of the memory block
    int id;            // user-defined ID
} MemoryBlock;

typedef struct {
    MemoryBlock blocks[MAX];
    int top;
} MemoryStack;

// Initialize the memory stack
void initialize(MemoryStack *stack) {
    stack->top = -1;
}

int isFull(MemoryStack *stack) {
    return stack->top == MAX - 1;
}

int isEmpty(MemoryStack *stack) {
    return stack->top == -1;
}

// Allocate real memory block and push onto stack
void allocateMemory(MemoryStack *stack, int id, size_t size) {
    if (isFull(stack)) {
        printf("Memory overflow: Stack is full.\n");
        return;
    }

    void* ptr = malloc(size);
    if (!ptr) {
        printf("Memory allocation failed for ID %d.\n", id);
        return;
    }

    stack->top++;
    stack->blocks[stack->top].address = ptr;
    stack->blocks[stack->top].size = size;
    stack->blocks[stack->top].id = id;

    printf("Allocated %zu bytes for Block ID %d at address %p\n", size, id, ptr);
}

// Deallocate top memory block from stack
void deallocateMemory(MemoryStack *stack) {
    if (isEmpty(stack)) {
        printf("Memory underflow: Stack is empty.\n");
        return;
    }

    MemoryBlock block = stack->blocks[stack->top];
    free(block.address);
    printf("Deallocated Block ID %d of size %zu bytes from address %p\n", block.id, block.size, block.address);
    stack->top--;
}

// Display all allocated memory blocks
void displayMemory(MemoryStack *stack) {
    if (isEmpty(stack)) {
        printf("No memory blocks allocated.\n");
        return;
    }

    printf("Allocated memory blocks (top to bottom):\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("  Block ID: %d, Size: %zu bytes, Address: %p\n",
               stack->blocks[i].id,
               stack->blocks[i].size,
               stack->blocks[i].address);
    }
}

int main() {
    MemoryStack memStack;
    initialize(&memStack);

    int choice, id;
    size_t size;

    while (1) {
        printf("\nMemory Management Using Real Stack Allocation\n");
        printf("1. Allocate Memory\n");
        printf("2. Deallocate Memory\n");
        printf("3. Display Allocated Blocks\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Block ID: ");
                scanf("%d", &id);
                printf("Enter size in bytes: ");
                scanf("%zu", &size);
                allocateMemory(&memStack, id, size);
                break;

            case 2:
                deallocateMemory(&memStack);
                break;

            case 3:
                displayMemory(&memStack);
                break;

            case 4:
                // Free any remaining memory before exit
                while (!isEmpty(&memStack)) {
                    deallocateMemory(&memStack);
                }
                printf("All memory blocks deallocated. Exiting.\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
