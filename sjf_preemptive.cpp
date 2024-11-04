#include <iostream>
using namespace std; 

struct Process {
string id;
int arrivalTime;
int burstTime;
int remainingTime;
int completionTime;
int waitingTime;
int turnaroundTime;
};

void calculateSJFPreemptive(Process processes[], int n) {
int completed = 0, currentTime = 0;
int minRemainingTime, shortestIndex;

for (int i = 0; i < n; i++) {
processes[i].remainingTime = processes[i].burstTime;
}


while (completed < n) {
minRemainingTime = 9999;
shortestIndex = -1;


for (int i = 0; i < n; i++) {
if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 &&
processes[i].remainingTime < minRemainingTime) {
minRemainingTime = processes[i].remainingTime;
shortestIndex = i;
}
}


if (shortestIndex == -1) {
currentTime++;
continue;
}
processes[shortestIndex].remainingTime--;
currentTime++;


if (processes[shortestIndex].remainingTime == 0) {
processes[shortestIndex].completionTime = currentTime;
processes[shortestIndex].turnaroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
processes[shortestIndex].waitingTime = processes[shortestIndex].turnaroundTime - processes[shortestIndex].burstTime;
completed++;
}
}
}

void displayResults(const Process processes[], int n) {
double totalWaitingTime = 0, totalTurnaroundTime = 0;

cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\t\tWaiting Time\tTurnaround Time\n";
cout << "----------------------------------------------------------------------------------------\n";
for (int i = 0; i < n; i++) {
cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t"
<< processes[i].burstTime << "\t\t" << processes[i].completionTime << "\t\t"
<< processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
totalWaitingTime += processes[i].waitingTime;
totalTurnaroundTime += processes[i].turnaroundTime;
}

cout << "\nAverage Waiting Time: " << totalWaitingTime / n;
cout << "\nAverage Turnaround Time: " << totalTurnaroundTime / n << endl;
}

int main() {
int n;
cout << "Enter the number of processes: ";
cin >> n;

Process* processes = new Process[n];


for (int i = 0; i < n; i++) {
cout << "\nEnter Process ID (letter or number): ";
cin >> processes[i].id;
cout << "Enter Arrival Time for Process " << processes[i].id << ": ";
cin >> processes[i].arrivalTime;
cout << "Enter Burst Time for Process " << processes[i].id << ": ";
cin >> processes[i].burstTime;
}


for (int i = 0; i < n - 1; i++) {
for (int j = i + 1; j < n; j++) {
if (processes[i].arrivalTime > processes[j].arrivalTime) {
swap(processes[i], processes[j]);
}
}
}


calculateSJFPreemptive(processes, n);


displayResults(processes, n);

delete[] processes;

return 0;
}
