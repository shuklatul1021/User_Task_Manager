#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char *description;         // Dynamically allocated
    int completed;
    char *timestamp;           // Dynamically allocated
    char *scheduled_time;      // Dynamically allocated
} Task;

Task **tasks = NULL;  // Array of pointers to Task structs
int task_count = 0;
int max_tasks = 2;  // Start with a small number of tasks and grow dynamically

// File to save and load tasks
const char *FILENAME = "database.txt";

// Function to dynamically grow the tasks array
void grow_task_array() {
    max_tasks *= 2;
    tasks = realloc(tasks, max_tasks * sizeof(Task*));
    if (tasks == NULL) {
        printf("Memory reallocation failed.\n");
        exit(1);
    }
}

// Function to save all tasks to the file
void save_tasks_to_file() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%d | %s | %d | %s | %s \n", 
                tasks[i]->id, 
                tasks[i]->description, 
                tasks[i]->completed, 
                tasks[i]->timestamp, 
                tasks[i]->scheduled_time);
    }

    fclose(file);
}

// Function to load tasks from the file
void load_tasks_from_file() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No existing task database found.\n");
        return;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (task_count == max_tasks) {
            grow_task_array();
        }

        tasks[task_count] = malloc(sizeof(Task));

        // Extract task details from file line
        char *id_str = strtok(buffer, "|");
        char *description = strtok(NULL, "|");
        char *completed_str = strtok(NULL, "|");
        char *timestamp = strtok(NULL, "|");
        char *scheduled_time = strtok(NULL, "\n");

        tasks[task_count]->id = atoi(id_str);

        tasks[task_count]->description = malloc(strlen(description) + 1);
        strcpy(tasks[task_count]->description, description);

        tasks[task_count]->completed = atoi(completed_str);

        tasks[task_count]->timestamp = malloc(strlen(timestamp) + 1);
        strcpy(tasks[task_count]->timestamp, timestamp);

        tasks[task_count]->scheduled_time = malloc(strlen(scheduled_time) + 1);
        strcpy(tasks[task_count]->scheduled_time, scheduled_time);

        task_count++;
    }

    fclose(file);
}

// Function to add a task
void add_task(const char *description, const char *scheduled_time) {
    if (task_count == max_tasks) {
        grow_task_array();  // Double the size of the task array if it's full
    }

    // Allocate memory for a new task
    tasks[task_count] = malloc(sizeof(Task));
    if (tasks[task_count] == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Allocate and copy description
    tasks[task_count]->description = malloc(strlen(description) + 1);
    strcpy(tasks[task_count]->description, description);

    // Allocate and copy scheduled time
    tasks[task_count]->scheduled_time = malloc(strlen(scheduled_time) + 1);
    strcpy(tasks[task_count]->scheduled_time, scheduled_time);

    // Get the current time and format it
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    tasks[task_count]->timestamp = malloc(20);  // Allocate space for timestamp
    strftime(tasks[task_count]->timestamp, 20, "%Y-%m-%d %H:%M:%S", t);

    // Assign the task details
    tasks[task_count]->id = task_count + 1;
    tasks[task_count]->completed = 0;

    task_count++;

    // Save tasks to file after adding a task
    save_tasks_to_file();
}

// Function to list all tasks
void list_tasks() {
    for (int i = 0; i < task_count; i++) {
        printf("ID: %d, Description: %s, Completed: %s, Added on: %s, Scheduled at: %s\n",
               tasks[i]->id,
               tasks[i]->description,
               tasks[i]->completed ? "Yes" : "No",
               tasks[i]->timestamp,
               tasks[i]->scheduled_time);
    }
}

// Function to list only completed tasks
void list_completed_tasks() {
    int found = 0;
    for (int i = 0; i < task_count; i++) {
        if (tasks[i]->completed) {
            printf("ID: %d, Description: %s, Completed on: %s, Scheduled at: %s\n",
                   tasks[i]->id,
                   tasks[i]->description,
                   tasks[i]->timestamp,
                   tasks[i]->scheduled_time);
            found = 1;
        }
    }
    if (!found) {
        printf("No completed tasks.\n");
    }
}

// Function to list only incomplete tasks
void list_incomplete_tasks() {
    int found = 0;
    for (int i = 0; i < task_count; i++) {
        if (!tasks[i]->completed) {
            printf("ID: %d, Description: %s, Added on: %s, Scheduled at: %s\n",
                   tasks[i]->id,
                   tasks[i]->description,
                   tasks[i]->timestamp,
                   tasks[i]->scheduled_time);
            found = 1;
        }
    }
    if (!found) {
        printf("No incomplete tasks.\n");
    }
}

// Function to remove a task and free memory
void remove_task(int id) {
    if (id < 1 || id > task_count) {
        printf("Invalid task ID.\n");
        return;
    }

    int index = id - 1;

    // Free the memory for the task being removed
    free(tasks[index]->description);
    free(tasks[index]->timestamp);
    free(tasks[index]->scheduled_time);
    free(tasks[index]);

    // Shift remaining tasks
    for (int i = index; i < task_count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    task_count--;

    // Save tasks to file after removing a task
    save_tasks_to_file();
}

// Function to mark a task as completed
void mark_task_completed(int id) {
    if (id < 1 || id > task_count) {
        printf("Invalid task ID.\n");
        return;
    }

    tasks[id - 1]->completed = 1;

    // Update the file after marking the task as completed
    save_tasks_to_file();
}

// Function to free all allocated memory before exiting
void free_all_tasks() {
    for (int i = 0; i < task_count; i++) {
        free(tasks[i]->description);
        free(tasks[i]->timestamp);
        free(tasks[i]->scheduled_time);
        free(tasks[i]);
    }
    free(tasks);
}


int main() {
    int choice;
    char description[256];
    char scheduled_time[100];

    // Initial allocation for the tasks array
    tasks = malloc(max_tasks * sizeof(Task*));
    if (tasks == NULL) {
        printf("Initial memory allocation failed.\n");
        exit(1);
    }

    // Load tasks from file on startup
    load_tasks_from_file();

    while (1) {
        printf("1. Add Task\n2. List Tasks\n3. Remove Task\n4. Mark Task as Completed\n5. Show Completed Tasks\n6. Show Incomplete Tasks\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0';  // Remove newline

                printf("Enter time to do the task (HH:MM or YYYY-MM-DD HH:MM): ");
                fgets(scheduled_time, sizeof(scheduled_time), stdin);
                scheduled_time[strcspn(scheduled_time, "\n")] = '\0';  // Remove newline

                add_task(description, scheduled_time);
                break;
            case 2:
                list_tasks();
                break;
            case 3:
                printf("Enter task ID to remove: ");
                int id;
                scanf("%d", &id);
                remove_task(id);
                break;
            case 4:
                printf("Enter task ID to mark as completed: ");
                scanf("%d", &id);
                mark_task_completed(id);
                break;
            case 5:
                list_completed_tasks();
                break;
            case 6:
                list_incomplete_tasks();
                break;
            case 7:
                free_all_tasks();  // Free all allocated memory
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
