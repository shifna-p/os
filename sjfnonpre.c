#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

typedef struct{
  char pname[20];
  int arr;
  int bt;
  int ct;
  int tat;
  int wt;
  int complete;
}process;

int shortest(process p[], int n, int time){
  int short1=-1;
  int minbt=INT_MAX;
  
for(int i=0;i<n;i++){
  if(p[i].arr<=time && !p[i].complete){
    if(p[i].bt<minbt){
      short1=i;
      minbt=p[i].bt;
    }
  }
  
}
return short1;
}

void sjfnon(process p[], int n){
  int time=0;
  int complete=0;
  
  
  
  while(complete<n){
    int st = shortest(p,n,time);
    if(st==-1){
      time++;
    }else{
      p[st].ct=p[st].bt+time;
      p[st].tat=p[st].ct-p[st].arr;
      p[st].wt=p[st].tat-p[st].bt;
      p[st].complete=1;
      time=p[st].ct;
      complete++;
    }
  }
      printf("name \t arrival\tburst\tcompletion\ttat\twt\n");
  for(int i=0;i<n;i++){

    printf("%s\t%d\t%d\t%d\t%d\t%d\n",p[i].pname,p[i].arr,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
  }
  double ttat=0;
  double twt=0;
  for(int i=0;i<n;i++){
   ttat +=p[i].tat;
   twt +=p[i].wt;
  }
  double atat=ttat/n;
  double awt=twt/n;
  printf("\nAverage Turnaround Time: %.2f\n", atat);
    printf("Average Waiting Time: %.2f\n", awt);
}
int main(){
  int n;
  printf("Enter process number : ");
  scanf("%d",&n);
  
  process p[n];
  
  for(int i=0;i<n;i++){
    printf("name : ");
    scanf("%s",p[i].pname);
    printf("arrival : ");
    scanf("%d",&p[i].arr);
    printf("burst :");
    scanf("%d",&p[i].bt);
    p[i].complete=0;  //initialising complete flag of all to 0
  }
  sjfnon(p,n);
  return 0;
}