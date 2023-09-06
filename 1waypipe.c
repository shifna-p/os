
#include<stdio.h>
#include<stdlib.h>    
#include<string.h>
#include<unistd.h>     

int main(){
    int pipe_fd[2];   

  if(pipe(pipe_fd)==-1){
    perror("pipe creation failed");
    return 1;
  } 

   pid_t pid = fork();  
   if(pid==-1){
     perror("fork failed"); 
    return 1;
   }
  if(pid==0){ //child process
   close(pipe_fd[1]); //write end closed in child
   char receive[100];
   read(pipe_fd[0],receive,sizeof(receive));
   close(pipe_fd[0]);  
   printf("child process\n");
   printf("child received : %s",receive);
 }else{
   //parent process
  close(pipe_fd[0]);  //close the read end
  char input[100];
  printf("parent process sending message\n");
  printf("Enter the message to child: ");
 fgets(input,sizeof(input),stdin); 
  write(pipe_fd[1],input,strlen(input)+1);  
  close(pipe_fd[1]);
 }
 return 0;
}