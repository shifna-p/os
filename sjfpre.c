#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char pname[20];
    int arr;
    int bt;
    int ct;
    int wt;
    int tat;
    int remainingTime; 
} process;

void sjf_preemptive(process p[], int n) {
    int time = 0;
    int completed = 0;
  int total_wt = 0; 
    int total_tat = 0; 

    while (completed < n) {
        int shortest = -1;
        int minbt = INT_MAX;  

        for (int i = 0; i < n; i++) {
            if (p[i].arr <= time && p[i].remainingTime < minbt && p[i].remainingTime > 0) {
                shortest = i;
                minbt = p[i].remainingTime;
            }
        }

        if (shortest == -1) {  
            time++;
            continue;
        }

        p[shortest].remainingTime--; 

        if (p[shortest].remainingTime == 0) {
            completed++;
            p[shortest].ct = time + 1;
            p[shortest].tat = p[shortest].ct - p[shortest].arr;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
        }

        time++;   
    }

    printf("name\tarrival time\tburst time\tcompletion time\ttat\twt\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i].pname, p[i].arr, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
     double avg_wt = (double)total_wt / n; // Calculate average waiting time
    double avg_tat = (double)total_tat / n; // Calculate average turnaround time
    printf("Average Waiting Time (avg wt): %.2f\n", avg_wt);
    printf("Average Turnaround Time (avg tat): %.2f\n", avg_tat);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process name: ");
        scanf("%s", p[i].pname);
        printf("Arrival time: ");
        scanf("%d", &p[i].arr);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
        p[i].remainingTime = p[i].bt;
    }

    sjf_preemptive(p, n);
    return 0;
}