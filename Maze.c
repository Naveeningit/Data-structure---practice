// Maze problem
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point data[MAX];
    int top;
} Stack;

// Stack operations
void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

void push(Stack* s, Point p) {
    if (!isFull(s)) {
        s->data[++(s->top)] = p;
    }
}

Point pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    Point invalid = {-1, -1};
    return invalid;
}

Point peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    Point invalid = {-1, -1};
    return invalid;
}

// Maze solver function
int solveMaze(int maze[][MAX], int visited[][MAX], int n, int m, Stack* path) {
    int dx[] = {1, 0, -1, 0};  // Down, Right, Up, Left
    int dy[] = {0, 1, 0, -1};

    Point start = {0, 0};
    push(path, start);
    visited[0][0] = 1;

    while (!isEmpty(path)) {
        Point curr = peek(path);

        if (curr.x == n - 1 && curr.y == m - 1) {
            return 1;  // Reached destination
        }

        int moved = 0;
        for (int i = 0; i < 4; i++) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];

            if (newX >= 0 && newX < n && newY >= 0 && newY < m &&
                maze[newX][newY] == 1 && visited[newX][newY] == 0) {
                Point next = {newX, newY};
                push(path, next);
                visited[newX][newY] = 1;
                moved = 1;
                break;
            }
        }

        if (!moved) {
            pop(path);  // Dead end, backtrack
        }
    }

    return 0;  // No path found
}

// Display the path
void printPath(Stack* path) {
    printf("\nPath from Start to End:\n");
    for (int i = 0; i <= path->top; i++) {
        printf("(%d, %d)\n", path->data[i].x, path->data[i].y);
    }
}

int main() {
    int n, m;
    int maze[MAX][MAX], visited[MAX][MAX] = {0};
    Stack path;

    printf("Enter maze size (rows cols): ");
    scanf("%d %d", &n, &m);

    printf("Enter maze matrix (0: block, 1: path):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &maze[i][j]);

    initStack(&path);

    if (maze[0][0] == 0 || maze[n-1][m-1] == 0) {
        printf("No path: Start or End is blocked.\n");
        return 0;
    }

    if (solveMaze(maze, visited, n, m, &path)) {
        printPath(&path);
    } else {
        printf("No path found through the maze.\n");
    }

    return 0;
}
