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

void sjf_scheduler(Queue *queue, FILE *output_file)
{
    // If the queue is empty, return
    if (is_queue_empty(queue))
    {
        return;
    }

    // Sort the processes in the queue based on burst time (shortest job first)
    Node *current = queue->front;
    Node *next_node = NULL;
    Process temp;

    while (current != NULL)
    {
        next_node = current->next;
        while (next_node != NULL)
        {
            if (current->process.burst_time > next_node->process.burst_time)
            {
                temp = current->process;
                current->process = next_node->process;
                next_node->process = temp;
            }
            next_node = next_node->next;
        }
        current = current->next;
    }

    // Simulate process execution in SJF order
    current = queue->front;
    while (current != NULL)
    {
        Process p = dequeue(queue);
        fprintf(output_file, "Process %s is assigned to CPU-2.\n", p.process_number);
        printf("Process %s is assigned to CPU-2.\n", p.process_number);
        // Simulate process execution
        fprintf(output_file, "Process %s is completed and terminated.\n", p.process_number);
        printf("Process %s is completed and terminated.\n", p.process_number);
        current = current->next;
    }
}

void round_robin_scheduler(Queue *queue, int quantum_time, FILE *output_file)
{
    // If the queue is empty, return
    if (is_queue_empty(queue))
    {
        return;
    }

    Node *current = queue->front;
    int remaining_time[MAX_PROCESSES];
    int idx_map[MAX_PROCESSES];
    int idx = 0;

    // Initialize remaining_time array with burst times of processes
    while (current != NULL)
    {
        remaining_time[idx] = current->process.burst_time;
        idx_map[idx] = idx;
        current = current->next;
        idx++;
    }

    // Simulate process execution using Round Robin algorithm
    int time = 0;
    int processed_count = idx;
    while (processed_count != 0)
    {
        current = queue->front;
        idx = 0;
        while (current != NULL)
        {
            // If remaining time for the process is 0, skip
            if (remaining_time[idx_map[idx]] == 0)
            {
                current = current->next;
                idx++;
                continue;
            }

            // Execute current process for the quantum time or remaining time, whichever is smaller
            int execute_time = (remaining_time[idx_map[idx]] < quantum_time) ? remaining_time[idx_map[idx]] : quantum_time;
            time += execute_time;
            remaining_time[idx_map[idx]] -= execute_time;

            // Print process execution message
            fprintf(output_file, "Process %s is assigned to CPU-2 and runs for %d seconds.\n", current->process.process_number, execute_time);
            printf("Process %s is assigned to CPU-2 and runs for %d seconds.\n", current->process.process_number, execute_time);
            // If process is completed, print completion message and decrement processed_count
            if (remaining_time[idx_map[idx]] == 0)
            {
                fprintf(output_file, "Process %s is completed and terminated.\n", current->process.process_number);
                printf("Process %s is completed and terminated.\n", current->process.process_number);
                processed_count--;
            }

            current = current->next;
            idx++;
        }
    }
}

void schedule_processes(FILE *output_file)
{
    // Schedule processes for CPU-1 (priority 0) using FCFS
    fcfs_cpu1_scheduler(output_file);

    // Schedule processes for CPU-2
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            // High priority user process queue (SJF)
            sjf_scheduler(&cpu2_queues[i], output_file);
        }
        else if (i == 1)
        {
            // Medium priority user process queue (Round Robin, quantum time 8)
            round_robin_scheduler(&cpu2_queues[i], QUANTUM_TIME_8, output_file);
        }
        else
        {
            // Low priority user process queue (Round Robin, quantum time 16)
            round_robin_scheduler(&cpu2_queues[i], QUANTUM_TIME_16, output_file);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open output file for writing
    FILE *output_file = fopen("output.txt", "w");
    if (!output_file)
    {
        printf("Error opening output file\n");
        return 1;
    }

    read_input_file(argv[1]);

    // Initialize queues
    init_queue(&cpu1_queue);
    for (int i = 0; i < 3; i++)
    {
        init_queue(&cpu2_queues[i]);
    }

    // Check resources and enqueue processes
    for (int i = 0; i < process_count; i++)
    {
        Process p = processes[i];
        if (p.priority == 0)
        {
            if (p.ram <= PRIORITY_0_RAM)
            {
                enqueue(&cpu1_queue, p);
                fprintf(output_file, "Process %s is queued to be assigned to CPU-1.\n", p.process_number);
                printf("Process %s is queued to be assigned to CPU-1.\n", p.process_number);
            }
            else
            {
                fprintf(output_file, "Process %s cannot be assigned to CPU-1 due to insufficient RAM.\n", p.process_number);
                printf("Process %s cannot be assigned to CPU-1 due to insufficient RAM.\n", p.process_number);
            }
        }
        else
        {
            if (p.ram <= available_ram)
            {
                enqueue(&cpu2_queues[p.priority - 1], p);
                fprintf(output_file, "Process %s is placed in the queue to be assigned to CPU-2.\n", p.process_number);
                printf("Process %s is placed in the queue to be assigned to CPU-2.\n", p.process_number);
                available_ram -= p.ram;
            }
            else
            {
                fprintf(output_file, "Process %s cannot be assigned to CPU-2 due to insufficient RAM.\n", p.process_number);
                printf("Process %s cannot be assigned to CPU-2 due to insufficient RAM.\n", p.process_number);
            }
        }
    }

    // Schedule processes
    schedule_processes(output_file);

    // Close the output file
    fclose(output_file);

    return 0;
}
