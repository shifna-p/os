#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;

    int pipefd1[2];
    int pipefd2[2];

    if (pipe(pipefd2) == -1 || pipe(pipefd1) == -1) {
        perror("pipe creation failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return 1;
    }
    
    if(pid ==0){
      close(pipefd1[1]);
      close(pipefd2[0]);
      
      read(pipefd1[0],&n,sizeof(n));
      
      printf("Child received %d from parent \n",n);
      
      for(int i=2; i<=n ;i++){
        if(prime(i)){
          write(pipefd2[1],&i,sizeof(i));
        }
      }
      close(pipefd1[0]);
      close(pipefd2[1]);
    }else{
        close(pipefd1[0]);
      close(pipefd2[1]);
     int primenum;
     printf(" enter the number : ");
     scanf("%d",&n);
     
     write(pipefd1[1],&n,sizeof(n));
     
     printf("Prime numbers are : ");
     while(read(pipefd2[0],&primenum,sizeof(primenum))){
     printf("%d ",primenum);
     }
     printf("\n");
     close(pipefd1[1]);
     close(pipefd2[0]);
    }
    return 0;
}