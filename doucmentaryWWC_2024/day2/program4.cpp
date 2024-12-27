#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

struct Task {
    int taskID;
    int priority;
    int executionTime;
    Task* next;
    
    Task(int id, int prio, int execTime)
        : taskID(id), priority(prio), executionTime(execTime), next(nullptr) {}
};

class TaskScheduler {
private:
    Task* head;

    void displayTasks() {
        if (!head) {
            cout << "No tasks in the queue.\n";
            return;
        }
        Task* temp = head;
        do {
            cout << "Task ID: " << temp->taskID
                      << ", Priority: " << temp->priority
                      << ", Execution Time: " << temp->executionTime << "s\n";
            temp = temp->next;
        } while (temp && temp != head);
    }

public:
    TaskScheduler() : head(nullptr) {}

    void insertTask(int taskID, int priority, int executionTime) {
        Task* newTask = new Task(taskID, priority, executionTime);
        if (!head) {
            head = newTask;
            head->next = head; // Circular Linked List
        } else if (head->priority < priority) {
            // Insert at head due to higher priority
            Task* temp = head;
            while (temp->next != head) temp = temp->next;
            temp->next = newTask;
            newTask->next = head;
            head = newTask;
        } else {
            // Insert in sorted order based on priority
            Task* current = head;
            while (current->next != head && current->next->priority >= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
        cout << "Task " << taskID << " added to the queue.\n";
    }

    void completeTask() {
        if (!head) {
            cout << "No tasks to complete.\n";
            return;
        }
        Task* temp = head;
        cout << "Completing Task ID: " << temp->taskID << "\n";
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Task* tail = head;
            while (tail->next != head) tail = tail->next;
            tail->next = head->next;
            head = head->next;
            delete temp;
        }
    }

    void simulateScheduler() {
        while (head) {
            displayTasks();
            cout << "Executing Task ID: " << head->taskID << "\n";
            this_thread::sleep_for(std::chrono::seconds(head->executionTime));
            completeTask();
        }
        cout << "All tasks completed.\n";
    }
};

int main() {
    TaskScheduler scheduler;
    int n;
    cout<<"Enter the number of task which you want to enter:";
    cin>>n;
    
    int ID[100],P[100],ET[100];
    cout<<"Enter the detail in following order: ID, Priority, Execution Time";
    for(int i=0;i<n;i++){
        cout<<"Enter the detail of "<<i+1<<"th task:";
        cin>>ID[i]>>P[i]>>ET[i];
    }
    for(int i=0;i<n;i++){
        scheduler.insertTask(ID[i], P[i], ET[i]);
    }
    
    scheduler.simulateScheduler();
    return 0;
}



/*************************************************************************************************************************************

Output:

Enter the number of task which you want to enter:5 4
Enter the detail in following order: ID, Priority, Execution TimeEnter the detail of 1th task:1
3
2
Enter the detail of 2th task:2
5
1
Enter the detail of 3th task:3
1
3
Enter the detail of 4th task:4
4
2
Task 1 added to the queue.
Task 2 added to the queue.
Task 3 added to the queue.
Task 4 added to the queue.
Task ID: 2, Priority: 5, Execution Time: 1s
Task ID: 4, Priority: 4, Execution Time: 2s
Task ID: 1, Priority: 3, Execution Time: 2s
Task ID: 3, Priority: 1, Execution Time: 3s
Executing Task ID: 2
Completing Task ID: 2
Task ID: 4, Priority: 4, Execution Time: 2s
Task ID: 1, Priority: 3, Execution Time: 2s
Task ID: 3, Priority: 1, Execution Time: 3s
Executing Task ID: 4
Completing Task ID: 4
Task ID: 1, Priority: 3, Execution Time: 2s
Task ID: 3, Priority: 1, Execution Time: 3s
Executing Task ID: 1
Completing Task ID: 1
Task ID: 3, Priority: 1, Execution Time: 3s
Executing Task ID: 3
Completing Task ID: 3
All tasks completed.

*********/
