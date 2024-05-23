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

Queue cpu1_queue;     
Queue cpu2_queues[3]; 
