#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
int ret;
pid_t pid;

int choice;
	pid=fork();

		if(pid==0)
			{
				printf(" In Child \n");
				ret=execlp("./pgm1","pgm1","2","3",(char*)0);
				if(ret<0)
					{
						perror("exec failed \n");
						exit(1);
					}
			}
		else
			{
				printf(" In parent \n");
			}
return 0;
}
