#include <stdio.h>

typedef struct {
    char pname[20];
    int parr;
    int pbt;
    int ct;
    int wt;
    int tat;
} process;

void fcfs(process p[], int n) {
    int time = 0;
    int total_wt = 0;
    int total_tat = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].parr) {
            time = p[i].parr;
        }
        p[i].ct = time + p[i].pbt;
        p[i].tat = p[i].ct - p[i].parr;
        p[i].wt = p[i].tat - p[i].pbt;

        time = p[i].ct;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("Process name\tArrival time\tBurst time\tCompletion time\tTurnaround time\tWaiting time\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pname, p[i].parr, p[i].pbt, p[i].ct, p[i].tat, p[i].wt);
    }

    double avg_wt = (double) total_wt / n;
    double avg_tat = (double) total_tat / n;

    printf("Average Waiting Time: %.2lf\n", avg_wt);
    printf("Average Turnaround Time: %.2lf\n", avg_tat);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process p[n];

    printf("Enter the details:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Process Name: ");
        scanf("%s", p[i].pname);
        printf("Arrival Time: ");
        scanf("%d", &p[i].parr);
        printf("Burst Time: ");
        scanf("%d", &p[i].pbt);
    }

    // Sorting in arriving order time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].parr > p[j + 1].parr) {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    fcfs(p, n);
    return 0;
}