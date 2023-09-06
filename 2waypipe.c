#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(){
int pipefd1[2];
int pipefd2[2];
char cm[100];

if(pipe(pipefd1)==-1||pipe(pipefd2)==-1){
perror("pipe failed");
return 1;
}

pid_t pid = fork();

if(pid==-1){
perror("fork failed");
return 1;
}
if(pid==0){
char receive[100];
char cm[100];
close(pipefd1[1]);
close(pipefd2[0]);
read(pipefd1[0], receive,sizeof(receive));
printf("\nChild process received message\n");
printf("\nEnter the message for parent : ");
fgets(cm,sizeof(cm),stdin);
write(pipefd2[1],cm,strlen(cm)+1);
close(pipefd1[0]);
close(pipefd2[1]);
}
else{
char receive2[100];
char pm[100];
close(pipefd1[0]);
close(pipefd2[1]);
printf("\nEnter the parent message : ");
fgets(pm,sizeof(pm),stdin);
write(pipefd1[1],pm,strlen(pm)+1);
read(pipefd2[0],receive2,sizeof(receive2));
printf("\nthe parent recieveed childs message\n");
close(pipefd1[1]);
close(pipefd2[0]);
}
return 0;
}