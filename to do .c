#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for each task
typedef struct Task {
    int id;
    char name[100];
    char category[50];
    int is_done; // 0 = Not done, 1 = Done
    struct Task* next;
} Task;

// Head of the linked list
Task* head = NULL;
int taskID = 1; // Unique ID for each task

// Function to add a task
void addTask() {
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->id = taskID++;

    printf("Enter task name: ");
    getchar(); // Clear input buffer
    fgets(newTask->name, 100, stdin);
    newTask->name[strcspn(newTask->name, "\n")] = '\0'; // Remove newline

    printf("Enter category: ");
    fgets(newTask->category, 50, stdin);
    newTask->category[strcspn(newTask->category, "\n")] = '\0'; // Remove newline

    newTask->is_done = 0;
    newTask->next = NULL;

    // Insert at end
    if (head == NULL) {
        head = newTask;
    } else {
        Task* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newTask;
    }

    printf("Task added successfully!\n");
}

// Function to view all tasks
void viewTasks() {
    if (head == NULL) {
        printf("No tasks found.\n");
        return;
    }

    Task* temp = head;
    printf("\n--- TASK LIST ---\n");
    while (temp != NULL) {
        printf("ID: %d | Name: %s | Category: %s | Status: %s\n",
            temp->id, temp->name, temp->category,
            temp->is_done ? "Done" : "Not Done");
        temp = temp->next;
    }
}

// Function to delete a task by ID
void deleteTask() {
    if (head == NULL) {
        printf("No tasks to delete.\n");
        return;
    }

    int id;
    printf("Enter Task ID to delete: ");
    scanf("%d", &id);

    Task* temp = head;
    Task* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Task with ID %d not found.\n", id);
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Task deleted successfully!\n");
}

// Function to mark a task as done
void markAsDone() {
    if (head == NULL) {
        printf("No tasks to update.\n");
        return;
    }

    int id;
    printf("Enter Task ID to mark as done: ");
    scanf("%d", &id);

    Task* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->is_done = 1;
            printf("Task marked as done!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Task with ID %d not found.\n", id);
}

// Function to free memory before exiting
void clearList() {
    Task* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Menu display
void showMenu() {
    printf("\n--- TO-DO LIST MENU ---\n");
    printf("1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Delete Task\n");
    printf("4. Mark Task as Done\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

// Main function
int main() {
    int choice;
    do {
        showMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: deleteTask(); break;
            case 4: markAsDone(); break;
            case 5: clearList(); printf("Goodbye, Ayush!\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}