#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define capacity 200

typedef struct process{
	char name[50];
	int relative_arrival_time,execution_time,iointerrupts,io_time;
} process;

typedef struct _queue{
int array[capacity];
int front;
int size;
}queue;



void push(queue* qq,int value);
int pop(queue* qq);
int not_finished(int arr[]);


int n;




int main()
{
    int i=0,pro_num;
    char file_name[250];
    process pr[capacity];
    printf("Please enter File Name: ");

    scanf("%s",file_name);

    FILE* ptr=fopen(file_name,"r");


    pro_num=read_fle(pr,ptr);

    for(i=0;i<pro_num;i++)
    printf("Process Name: %s, Arrival: %d, Execution: %d i/o: %d, i/o execution: %d\n",pr[i].name,pr[i].relative_arrival_time,pr[i].execution_time
            ,pr[i].iointerrupts,pr[i].io_time);

    n=pro_num;
    queue q;
    q.front=0;
    q.size=0;
    int time=0;
    int waiting_time[pro_num];
    int running_time[pro_num]; //
    int finishing_time[pro_num];
    int finished[pro_num];
    int running_process;
    int busy=0;
    int arrival_time[pro_num];

    int x=0;
    int ft=0;
    int inct=1;

    int io[pro_num];
    int io_runing_time[pro_num];
    int pro_num_io;

    int io_finished_time[pro_num];
    memset(io_finished_time, -1, sizeof(io_finished_time));

    int io_once[pro_num];
    memset(io_once, 0, sizeof(io_once));


    int turn_around_time[pro_num];
    float average_waiting_time=0;
    float average_turnaround_time=0;



    for( i=0;i<pro_num;i++) finished[i]=0;
    for( i=0;i<pro_num;i++) waiting_time[i]=0;
    for( i=0;i<pro_num;i++) running_time[i]=0;
    for( i=0;i<pro_num;i++){
        arrival_time[i]=ft+pr[i].relative_arrival_time ;
        ft = arrival_time[i];
       // printf("%d\n",arrival_time[i]);
    }
    for( i=0;i<pro_num;i++) io_runing_time[i]=0;


 while (not_finished(finished))
    {
    for(i=0;i<pro_num;i++)
        if(arrival_time[i] == time){ push(&q,i);
      //  printf("process %s is pushed at time %d\n",pr[i].name,time);
        }

         for (i = 0; i < pro_num; i++)
        {
            if (io_finished_time[i] == time){
                push(&q, i);
             //   printf("process %s is pushed at time %d\n",pr[i].name,time);
                io_once[i]=1;
            }
        }
        if(busy == 1)
        {

            running_time[running_process]++;


            if(running_time[running_process] == pr[running_process].execution_time)
            {
                busy = 0;
                finished[running_process]=1;
                finishing_time[running_process]=time;


                printf("Process %d has finished processing\n",running_process+1);
            }
             if(io[running_process]==time&&finished[running_process]==0&&io_once[running_process]==0){
                  // arrival_time[running_process]=time+pr[running_process].io_time;
                    io_finished_time[running_process]=time+pr[running_process].io_time;
                   busy=0;

            }
        }


        if(busy == 0 && q.size > 0)
        {
              running_process=pop(&q);
            //  printf("process %s is poped at time %d\n",pr[running_process].name,time);

              busy=1;
              io[running_process]=time+pr[running_process].iointerrupts;


        }

        for( i=q.front;i<(q.front+q.size);i++) waiting_time[q.array[i]]++;

        time++;

    }

     for( i=0;i<pro_num;i++) turn_around_time[i]=finishing_time[i]-arrival_time[i];

    for( i=0;i<pro_num;i++)
    {
        printf("process %d: finishing time: %d, waiting time: %d, turn around time: %d.\n",i+1,finishing_time[i],waiting_time[i],turn_around_time[i]);
    }

    for( i=0;i<pro_num;i++){
        average_waiting_time=average_waiting_time+waiting_time[i];
    }
    average_waiting_time=average_waiting_time/pro_num;

    for( i=0;i<pro_num;i++){
        average_turnaround_time=average_turnaround_time+turn_around_time[i];
    }
    average_turnaround_time=average_turnaround_time/pro_num;

    printf("average waiting time = %5f \n average turn around time = %5f \n",average_waiting_time,average_turnaround_time);



return 0;
}

int read_fle(process p[],FILE* ptr)
{
    int i;
	char first[50];
	int cnt=0;
    while (fscanf(ptr,"%s",first) != EOF)
    {
        if(first[0] == 'x') break;
        else
            {
               strcpy(p[cnt].name,first);
               for(i=0;i<4;i++)
               {
                   if(!i) fscanf(ptr,"%d",&p[cnt].relative_arrival_time);
                   else if(i == 1) fscanf(ptr,"%d",&p[cnt].execution_time);
                   else if(i == 2)  fscanf(ptr,"%d",&p[cnt].iointerrupts);
                   else if(i == 3) fscanf(ptr,"%d",&p[cnt].io_time);
               }
    }
      cnt++;
    }
	fclose(ptr);
	return cnt;
}


void push(queue* qq,int value){
int idx=(qq->front+qq->size)%capacity;
qq->array[idx]=value;
qq->size++;
}

int pop(queue* qq)
{
int x=qq->array[(qq->front)%capacity];
qq->size--;
qq->front++;
return x;
}
int not_finished(int arr[])
{
    int i;
    for(i=0;i<n;i++)
    {
        if(arr[i] == 0)
            return 1;
    }
    return 0;
}

