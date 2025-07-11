// car manufacturers using Tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CarNode {
    char carName[50];
    char manufacturer[50];
    char carType[50];
    struct CarNode* left;
    struct CarNode* right;
} CarNode;

// Create a new node
CarNode* createNode(const char* name, const char* manufacturer, const char* type) {
    CarNode* newNode = (CarNode*)malloc(sizeof(CarNode));
    strcpy(newNode->carName, name);
    strcpy(newNode->manufacturer, manufacturer);
    strcpy(newNode->carType, type);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into binary search tree
CarNode* insert(CarNode* root, const char* name, const char* manufacturer, const char* type) {
    if (root == NULL) {
        return createNode(name, manufacturer, type);
    }

    if (strcmp(name, root->carName) < 0) {
        root->left = insert(root->left, name, manufacturer, type);
    } else {
        root->right = insert(root->right, name, manufacturer, type);
    }

    return root;
}

// Search car in tree
void searchCar(CarNode* root, const char* name) {
    if (root == NULL) {
        printf("Car '%s' not found in the database.\n", name);
        return;
    }

    int cmp = strcmp(name, root->carName);

    if (cmp == 0) {
        printf("Car Name: %s\n", root->carName);
        printf("Manufacturer: %s\n", root->manufacturer);
        printf("Car Type: %s\n", root->carType);
    } else if (cmp < 0) {
        searchCar(root->left, name);
    } else {
        searchCar(root->right, name);
    }
}

// Free memory
void freeTree(CarNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    CarNode* root = NULL;

    // Inserting sample car data
    root = insert(root, "Creta", "Hyundai", "SUV");
    root = insert(root, "City", "Honda", "Sedan");
    root = insert(root, "Swift", "Maruti Suzuki", "Hatchback");
    root = insert(root, "Fortuner", "Toyota", "SUV");
    root = insert(root, "Verna", "Hyundai", "Sedan");

    char query[50];
    printf("Enter the car name to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0'; // remove newline

    searchCar(root, query);

    freeTree(root);
    return 0;
}
