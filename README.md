README for Process Scheduler
Overview
This program simulates a process scheduler for a dual CPU system, handling different priority processes using various scheduling algorithms. The program reads input from a file, checks resource availability, queues the processes, and schedules them according to their priority.

Features
CPU-1 (Priority 0): Uses First-Come-First-Serve (FCFS) scheduling.
CPU-2:
Priority 1: Uses Shortest Job First (SJF) scheduling.
Priority 2: Uses Round Robin with a quantum time of 8 seconds.
Priority 3: Uses Round Robin with a quantum time of 16 seconds

Input File Format
The input file should contain process information in the following format (one process per line):
process_number,arrival_time,priority,burst_time,ram,cpu


README for Process Scheduler
Overview
This program simulates a process scheduler for a dual CPU system, handling different priority processes using various scheduling algorithms. The program reads input from a file, checks resource availability, queues the processes, and schedules them according to their priority.

Features
CPU-1 (Priority 0): Uses First-Come-First-Serve (FCFS) scheduling.
CPU-2:
Priority 1: Uses Shortest Job First (SJF) scheduling.
Priority 2: Uses Round Robin with a quantum time of 8 seconds.
Priority 3: Uses Round Robin with a quantum time of 16 seconds.
Input File Format
The input file should contain process information in the following format (one process per line):


Usage
Compile the program:

gcc -o os1 os1.c

Run the program with the input file as an argument:

./os1 input.txt


Output
The program generates an output.txt file that logs the scheduling activities. It also prints the same information to the console. The output includes:

Queuing Messages:

Indicates which processes are queued for CPU-1 and CPU-2.
Assignment Messages:

Details when a process is assigned to a CPU.
Completion Messages:

Confirms when a process has completed execution and is terminated.

Example Output:

Process P1 is queued to be assigned to CPU-1.
Process P1 is assigned to CPU-1.
Process P1 is completed and terminated.
Process P2 is placed in the queue to be assigned to CPU-2.
Process P2 is assigned to CPU-2.
Process P2 is completed and terminated.
Process P3 is placed in the queue to be assigned to CPU-2.
Process P3 is assigned to CPU-2 and runs for 8 seconds.
Process P3 is assigned to CPU-2 and runs for 8 seconds.
Process P3 is completed and terminated.

Source Code Structure

Process Struct: Defines a process's attributes.
Node Struct: Defines a node for the queue.
Queue Struct: Manages the queue operations.
Helper Functions: Includes queue operations (init_queue, is_queue_empty, enqueue, dequeue), and file reading (read_input_file).

Scheduling Functions
FCFS Scheduler for CPU-1
SJF Scheduler for Priority 1 on CPU-2
Round Robin Scheduler for Priority 2 and 3 on CPU

Steps
Read Input File: Parse the process details and store them in an array.
Initialize Queues: Set up the queues for CPU-1 and CPU-2.
Check Resources and Enqueue Processes: Based on priority and resource availability.
Schedule Processes: Using the appropriate scheduling algorithms for each queue.
Output Results: Write scheduling details to output.txt and print them to the console.

Compilation and Execution
To compile and run the program:

gcc -o os1 os1.c
./os1 input.txt

Make sure the input.txt file is correctly formatted and placed in the same directory as the executable. The output will be written to output.txt and also displayed in the console.

Notes
Ensure sufficient RAM is available for each process before queuing.
The program handles process scheduling and resource management efficiently across different CPU priorities.


