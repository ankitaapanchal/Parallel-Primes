#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[])
{
int process_ids[atoi(argv[3])];
pid_t pid;

int start=atoi(argv[1]);
int end=atoi(argv[2]);
int number_of_calls=atoi(argv[3]);

for(int i=0; i<number_of_calls; i++)
{
pid=fork();
int th=i;
process_ids[i]=pid;

if(pid==0)
{
char startrange[10];
char endrange[10];
//Calculate the subrange for child process
snprintf(startrange, 10, "%d", start+(end-start)*i/number_of_calls);
snprintf(endrange, 10, "%d", start+(end-start)*(i+1)/number_of_calls);

char* arguments[4];// Array that can hold up to 4 strings
arguments[0]="./countprimes";
arguments[1]=startrange;// Pass the subrange as command-line arguments
arguments[2]=endrange;
arguments[3]=NULL;
execvp("./countprimes", arguments);
break;
}
}
if(pid!=0)
{
int result=0;
for(int i=0; i<atoi(argv[3]); i++)
{
int status;
waitpid(process_ids[i], &status, 0);
result=result+WEXITSTATUS(status);
}
printf("Count is %d\n", result);
}
return 0;
}

