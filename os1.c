#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PROCESSES 100
#define RAM_SIZE 2048
#define PRIORITY_0_RAM 512
#define CPU_COUNT 2
#define QUANTUM_TIME_8 8
#define QUANTUM_TIME_16 16

typedef struct
{
    char process_number[5];
    int arrival_time;
    int priority;
    int burst_time;
    int ram;
    int cpu;
} Process;

typedef struct Node
{
    Process process;
    struct Node *next;
} Node;

typedef struct
{
    Node *front;
    Node *rear;
} Queue;

Process processes[MAX_PROCESSES];
int process_count = 0;
int available_ram = RAM_SIZE - PRIORITY_0_RAM;

Queue cpu1_queue;     // For priority 0
Queue cpu2_queues[3]; // For priorities 1, 2, and 3

void init_queue(Queue *queue)
{
    queue->front = queue->rear = NULL;
}

bool is_queue_empty(Queue *queue)
{
    return queue->front == NULL;
}

void enqueue(Queue *queue, Process process)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->process = process;
    new_node->next = NULL;
    if (is_queue_empty(queue))
    {
        queue->front = queue->rear = new_node;
    }
    else
    {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

Process dequeue(Queue *queue)
{
    if (is_queue_empty(queue))
    {
        printf("Queue is empty\n");
        exit(1);
    }
    Node *temp = queue->front;
    Process process = temp->process;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp);
    return process;
}

void read_input_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file\n");
        exit(1);
    }
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^,],%d,%d,%d,%d,%d",
               processes[process_count].process_number,
               &processes[process_count].arrival_time,
               &processes[process_count].priority,
               &processes[process_count].burst_time,
               &processes[process_count].ram,
               &processes[process_count].cpu);
        process_count++;
    }
    fclose(file);
}

void fcfs_cpu1_scheduler(FILE *output_file)
{
    while (!is_queue_empty(&cpu1_queue))
    {
        Process p = dequeue(&cpu1_queue);
        fprintf(output_file, "Process %s is assigned to CPU-1.\n", p.process_number);
        printf("Process %s is assigned to CPU-1.\n", p.process_number);
        // Simulate process execution
        fprintf(output_file, "Process %s is completed and terminated.\n", p.process_number);
         printf("Process %s is completed and terminated.\n", p.process_number);
    }
}

