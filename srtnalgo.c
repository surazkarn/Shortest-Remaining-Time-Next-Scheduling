#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

struct process_struct
{
  int processID;
  int arivalTime;
  int burstTime;
  int ct,wt,tarivalTime,responseTime,start_time;
}ps[100];

int findmax(int a, int b)
{
    return a>b?a:b;
}

int findmin(int a, int b)
{
    return a<b?a:b;
}

int main()
{
    
    int n;
    float burstTime_remaining[100];
    bool is_completed[100]={false},is_first_process=true;
    int current_time = 0;
    int completed = 0;;
    float sum_tarivalTime=0,sum_wt=0,sum_responseTime=0,total_idle_time=0,length_cycle,prev=0;
    float cpu_utilization;

    int max_completion_time,min_arrival_time;

    printf("Enter number of processes: ");
    scanf("%d",&n);   
    for(int i=0;i<n;i++)
    {
        printf("\nEnter Arrival Time of P%d : ",i);
        scanf("%d",&ps[i].arivalTime);
        ps[i].processID = i ;
    }
    
    for(int i=0;i<n;i++)
    {
        printf("\nEnter Burst Time P%d : ",i);
        scanf("%d",&ps[i].burstTime);
        burstTime_remaining[i]= ps[i].burstTime;
    }
   
    while(completed!=n)
    {
      
        int min_index = -1;
        int minimum = INT_MAX;
        for(int i = 0; i < n; i++) {
            if(ps[i].arivalTime <= current_time && is_completed[i] == false) {
                if(burstTime_remaining[i] < minimum) {
                    minimum = burstTime_remaining[i];
                    min_index = i;
                }
                if(burstTime_remaining[i]== minimum) {
                    if(ps[i].arivalTime < ps[min_index].arivalTime) {
                        minimum= burstTime_remaining[i];
                        min_index = i;
                    }
                }
            }
        }
  
        
        if(min_index==-1)
        {
            current_time++;
        }
        else
        {
            if(burstTime_remaining[min_index] == ps[min_index].burstTime)
            {
                        ps[min_index].start_time = current_time;
                        total_idle_time += (is_first_process==true) ? 0 : (ps[min_index].start_time -  prev);
                        is_first_process=false;
            }
            burstTime_remaining[min_index] -= 1;
            current_time++; 
            prev=current_time;
            if(burstTime_remaining[min_index] == 0)
            {
                ps[min_index].ct = current_time;
                ps[min_index].tarivalTime = ps[min_index].ct - ps[min_index].arivalTime;
                ps[min_index].wt= ps[min_index].tarivalTime - ps[min_index].burstTime;
                ps[min_index].responseTime = ps[min_index].start_time - ps[min_index].arivalTime;
            
             
                sum_tarivalTime +=ps[min_index].tarivalTime;
                sum_wt += ps[min_index].wt;
                sum_responseTime += ps[min_index].responseTime;
                completed++;
                is_completed[min_index]=true;
               
            }
        }
    }
     
    printf("\nAverage Turn Around time= %f ",(float)sum_tarivalTime/n);
    printf("\nAverage Waiting Time= %f ",(float)sum_wt/n);
    printf("\nAverage Response Time= %f ",(float)sum_responseTime/n);
   
    return 0;
}
