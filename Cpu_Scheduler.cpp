#include <iostream>
using namespace std;

typedef struct {
    char name[10];
    int length;
} Job;


typedef struct {
    Job *heap;
    int size;
    int capacity;
} PriorityQueue;

// Initialize a priority queue
PriorityQueue* initPriorityQueue(int n) {
    PriorityQueue* pq = new PriorityQueue;
    pq->heap = new Job[n];
    pq->size = 0;
    pq->capacity = n;
    return pq;
}

// Swap two jobs
void swap(Job* a, Job* b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify down
void heapifyDown(PriorityQueue* pq, int ind) {
    int left = 2 * ind + 1;
    int right = 2 * ind + 2;
    int smallest = ind;

    if (left < pq->size && pq->heap[left].length < pq->heap[smallest].length) {
        smallest = left;
    }

    if (right < pq->size && pq->heap[right].length < pq->heap[smallest].length) {
        smallest = right;
    }

    if (smallest != ind) {
        swap(&pq->heap[ind], &pq->heap[smallest]);
        heapifyDown(pq, smallest);
    }
}

// Enqueue a job into the priority queue
void enqueue(PriorityQueue* pq, Job job) {
    if (pq->size == pq->capacity) {
        cout<<"Priority queue is full.\n";
        return;
    }

    int ind = pq->size;
    pq->heap[ind] = job;
    pq->size++;

    while (ind > 0 && pq->heap[ind].length < pq->heap[(ind - 1) / 2].length) {
        swap(&pq->heap[ind], &pq->heap[(ind - 1) / 2]);
        ind = (ind - 1) / 2;
    }
}

// Dequeue a job from the priority queue
Job dequeue(PriorityQueue* pq) {
    if (pq->size == 0) {
        cout<<"Priority queue is empty.\n";
        Job emptyJob = {"", -1}; // Return empty job
        return emptyJob;
    }

    Job minJob = pq->heap[0];
    pq->size--;
    pq->heap[0] = pq->heap[pq->size];
    heapifyDown(pq, 0);

    return minJob;
}

int main() {
    // Define jobs
    Job jobs[] = {
        {"Job 1", 5},
        {"Job 2", 2},
        {"Job 3", 7},
        {"Job 4", 1},
        {"Job 5", 4}
    };
    int numJobs = sizeof(jobs) / sizeof(jobs[0]);
    cout<<"JOBs :\n";
   
       for(int i=0;i<numJobs;i++) {

        cout<<"Processing "<< jobs[i].name<<" (Length = "<< jobs[i].length <<" units)\n";
    }

    // Initialize priority queue
    PriorityQueue* pq = initPriorityQueue(numJobs);

    // Enqueue jobs into the priority queue
    for (int i = 0; i < numJobs; i++) {
        enqueue(pq, jobs[i]);
    }

    // Simulate SJF scheduling
    cout<<"-- Starting SJF Scheduling Simulation --\n";
    while (pq->size > 0) {
        Job job = dequeue(pq);
        printf("Processing %s (Length = %d units)\n", job.name, job.length);
    }
    printf("-- SJF Scheduling Simulation Complete --\n");

    // Free memory
    free(pq->heap);
    free(pq);

    return 0;
}