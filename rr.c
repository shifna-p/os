#include<stdio.h>

int main(){
  int i,at[10],bt[10],wt,tat,n,count=0,y,time=0,quant,temp[10];
  
  float atat,awt;
  
  printf("Enter the number of processes : ");
  scanf("%d",&n);
  y=n;
  
  for(i=0;i<n;i++){
    printf("Enter arrival time of %d",i+1);
    scanf("%d",&at[i]);
    printf("Enter burst time of %d",i+1);
    scanf("%d",&bt[i]);
    temp[i]=bt[i];
  }
  
  printf("Quantum = ");
  scanf("%d",&quant);
  printf("\n process\t\t Burst time \t\t tat \t\t waiting time ");
  for(time=0,i=0;y!=0;){
    if(temp[i]<=quant && temp[i]>0){
      time=time+temp[i];
      temp[i]=0;
      count=1;
    }else if(temp[i]>0){
      temp[i]=temp[i]-quant;
      time=time+quant;
    }
    if(temp[i]==0 && count==1){
      y--;
      tat=time-at[i];
      wt=tat-bt[i];
      printf("\n%d\t\t%d\t\t%d\t\t%d",i+1,bt[i],tat,wt);
      count=0;
    }
    if(i==n-1){
      i=0;
    }else if(at[i+1]<=time){
      i++;
    }else{
      i=0;
    }
  }
  
  atat=tat*1.0/n;
  awt=wt*1.0/n;
  printf("\nAverage tat : \t%f",atat);
  printf("\nAverage wt : \t%f",awt);
  
  return 0;
}