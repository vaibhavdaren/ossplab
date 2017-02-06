#include<stdio.h>
typedef struct process
{
int id;
int wait;
int burst;
}process;
struct process pro[10];
struct process temp[20];

void table(struct process pro[],int nop);
void gantt(struct process pro[],int nop);
int getdata();
void incwait(int tempburst,int id);
void init();

int nop;

main()
{
struct process tmppro;
int choice,quantum;
int i,j,x,z,ret;
int ans,rrwt;
float rrawt,rratrt,fcfsawt,fcfsatrt,sjfatrt,sjfawt;
int procount,t,tburst[10];
do
{
printf("\t\t* * * * * * MENU * * * * * * \n");
printf("\t\t1.FCFS\n\t\t2.SJF\n\t\t3.Round Robin");
printf("\n\nPlease enter your choice : ");
scanf("%d",&choice);

switch(choice)
{
case 1:
{
init();
nop=getdata();
table(pro,nop);
gantt(pro,nop);
fcfsawt=0;
fcfsatrt=0;
for(i=nop-1;i>=0;i--)
{
pro[i].wait=0;
for(j=0;j<i;j++)
{
pro[i].wait=pro[i].wait+pro[j].burst;
}
}
for(i=0;i<nop;i++)
{
printf("\nP%d Wait Time : %d",pro[i].id,pro[i].wait);
printf("\nP%d Turn Around Time : %d",pro[i].id,(pro[i].wait+pro[i].burst));
fcfsawt=fcfsawt+pro[i].wait;
fcfsatrt=fcfsatrt+(pro[i].wait+pro[i].burst);
}
printf("\n\nAWT of FCFS : %f",fcfsawt/nop);
printf("\n\nATRT of FCFS : %f",fcfsatrt/nop);
break;
}
case 2:
{
init();
nop=getdata();
printf("\nTable before arranging ...\n");
table(pro,nop);
for(i=1;i<nop;i++)
{
for(j=0;j<nop-i;j++)
{
if(pro[j].burst>pro[j+1].burst)
{
tmppro=pro[j];
pro[j]=pro[j+1];
pro[j+1]=tmppro;
}
}
}
printf("\nTable after arranging ...\n");
table(pro,nop);
gantt(pro,nop);
sjfawt=0;
sjfatrt=0;
for(i=nop-1;i>=0;i--)
{
pro[i].wait=0;
for(j=0;j<i;j++)
{
pro[i].wait=pro[i].wait+pro[j].burst;
}
}
for(i=0;i<nop;i++)
{
printf("\nP%d Wait Time : %d",pro[i].id,pro[i].wait);
printf("\nP%d Turn Around Time : %d",pro[i].id,(pro[i].wait+pro[i].burst));
sjfawt=sjfawt+pro[i].wait;
sjfatrt=sjfatrt+(pro[i].wait+pro[i].burst);
}
printf("\n\nAWT of SJF : %f",sjfawt/nop);
printf("\n\nATRT of SJF : %f",sjfatrt/nop);
break;
}
case 3:
{
init();
j=0;
ret=0;
nop=getdata();
for(i=0;i<nop;i++)
tburst[i]=pro[i].burst;
printf("\nPlease enter the time quantum : ");
scanf("%d",&quantum);
for(i=0;i<nop;i++)
{
if(pro[i].burst>0)
{
if(pro[i].burst>quantum)
{
temp[j].id=pro[i].id;
temp[j].burst=quantum;
pro[i].burst=pro[i].burst-quantum;
j++;
incwait(quantum,pro[i].id);
}
else
{
temp[j]=pro[i];
j++;
incwait(pro[i].burst,pro[i].id);
pro[i].burst=0;
}
}
if(i==nop-1)
{
for(z=0;z<nop;z++)
{
if(pro[z].burst!=0)
{
i=-1;
break;
}
else
if(z==(nop-1)) ret=1;
}
}
if(ret==1) break;
}
table(temp,40);
gantt(temp,40);
printf("\n\nRound Robin awt and atrt : ");
rrawt=0;
rratrt=0;
for(i=0;i<nop;i++)
{
printf("\nP%d Wait Time : %d",pro[i].id,pro[i].wait);
printf("\nP%d Turn Around Time : %d",pro[i].id,(pro[i].wait+tburst[i]));
rrawt=rrawt+pro[i].wait;
rratrt=rratrt+(pro[i].wait+tburst[i]);
}
printf("\n\nAWT of RR : %f",rrawt/nop);
printf("\n\nATRT of RR : %f",rratrt/nop);
break;
}
}
printf("\n\nPress 1 to cont ...");
scanf("%d",&ans);
}
while(ans==1);
}

void incwait(int tempburst,int id)
{
int i=0;
for(i=0;i<nop;i++)
{
if(pro[i].id!=id && pro[i].burst>0)
pro[i].wait=pro[i].wait+tempburst;
}
}

void init()
{
int i;
nop=0;
for(i=0;i<10;i++)
{
pro[i].burst=0;
pro[i].id=0;
pro[i].wait=0;
}
for(i=0;i<20;i++)
{
temp[i].burst=0;
temp[i].id=0;
temp[i].wait=0;
}
}



void table(struct process pro[],int nop)
{
int i;
printf("\n\n\n* * * * * * * PROCESS TABLE * * * * * * *\n\n");
printf("\nProcess Name Burst Time");
for(i=0;i<nop;i++)
{
if(pro[i].id==0)
break;
printf("\nP%d\t\t%d\t\t%d",i,pro[i].id,pro[i].burst);
}
}


void gantt(struct process pro[],int nop)
{
int t=0,i;
int procount=0;
printf("\n\n\n* * * * * * * GANTT CHART * * * * * * *\n\n");
i=0;
while(pro[i].id>0)
{
procount++;
i++;
}
printf("\nÚ");
for(i=0;i<procount;i++)
printf("ÄÄÄÄÄÄÄÂ");
printf("\n³");
for(i=0;i<procount;i++)
printf(" P%d ³",pro[i].id);
printf("\nÀ");
for(i=0;i<procount;i++)
printf("ÄÄÄÄÄÄÄÁ");
printf("\n");
for(i=0;i<procount;i++)
{
printf("%d\t",t);
t=t+pro[i].burst;
}
printf("%d",t);
}


int getdata()
{
int i,nop;
printf("\n\nPlease enter the number of processes : ");
scanf("%d",&nop);
printf("\nPlease enter the ID and Burst time of each process : ");
printf("\n");
for(i=0;i<nop;i++)
{
printf("\nID : P%d",i+1);
pro[i].id=i+1;
printf("\nBurst Time : ");
scanf("%d",&pro[i].burst);
}
return nop;
}