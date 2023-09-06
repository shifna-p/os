#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(){
  int pipefd[2];
  char input[100];
  int length;
  int palindrome=1;
  
  if(pipe(pipefd)==-1){
    perror("pipe creation failed");
    return 1;
  }
  
  pid_t pid= fork();
  
  if(pid==-1){
    perror("fork failed");
    return 1;
  }
  
  if(pid==0){
  //child process
  
  close(pipefd[1]);
  read(pipefd[0],input,sizeof(input));
  printf("\nchild process received string %s\n",input);
  length=strlen(input);
  for(int i=0;i<length/2;i++){
    if(input[i]!=input[length-i-1]){
      palindrome=0;
      break;
    }
  }
  if(palindrome){
    printf("\nthe string '%s' is palindrome\n",input);
  }else{
  printf("\nthe string '%s' not palindrome\n",input);
  }
  close(pipefd[0]);
  }
  else{
    close(pipefd[0]);
    printf("\nenter the string : ");
    scanf("%s",input);
    
    write(pipefd[1],input,strlen(input)+1);
    close(pipefd[1]);
  }
  return 0;
}